/**
 * This file is created at Almende B.V. It is open-source software and part of the Common 
 * Hybrid Agent Platform (CHAP). A toolbox with a lot of open-source tools, ranging from 
 * thread pools and TCP/IP components to control architectures and learning algorithms. 
 * This software is published under the GNU Lesser General Public license (LGPL).
 *
 * It is not possible to add usage restrictions to an open-source license. Nevertheless,
 * we personally strongly object against this software being used by the military, in the
 * bio-industry, for animal experimentation, or anything that violates the Universal
 * Declaration of Human Rights.
 *
 * @author               Marc Hulscher
 * @copyright            DO bots
 * @date                 dec 10, 2013
 * @license              Apache Licence
 */

#include "Txt2MorseModule.h"

namespace rur {

Txt2MorseModule::Txt2MorseModule():
  ns_socket(NULL),
  cmd_socket(NULL),
  debug(0),
  cliParam(0)
{
  const char* const channel[2] = {"readTxt", "writeMorse"};
  cliParam = new Param();
  context = new zmq::context_t(1);
  pthread_mutex_init(&cmdMutex, NULL);
  pthread_create(&cmdThread, 0, readCommandsHelper, this);
  portTxtIn.sock = new zmq::socket_t(*context, ZMQ_REP);
  portTxtIn.ready = true;
  zmq_sockets.push_back(&portTxtIn);
  portMorseOut.sock = new zmq::socket_t(*context, ZMQ_REQ);
  portMorseOut.ready = true;
  zmq_sockets.push_back(&portMorseOut);
}

Txt2MorseModule::~Txt2MorseModule() {
  delete cliParam;
  delete portTxtIn.sock;
  delete portMorseOut.sock;
}

void Txt2MorseModule::Init(std::string & name) {
  cliParam->module_id = name;
  
  std::cout << "Connecting to name server..." << std::endl;
  ns_socket = new zmq::socket_t(*context, ZMQ_REQ);
  try {
    ns_socket->connect("tcp://127.0.0.1:10101"); // port to connect to, REQ/REP
  } catch (zmq::error_t & e) {
    std::cerr << "Error: Could not connect to the name server: = " << e.what() << std::endl;
  }
  cmd_socket = new zmq::socket_t(*context, ZMQ_REP);
  
  std::string zmqPortName;
  std::stringstream zmqSs;
  {
    pns_record record;
    zmqSs.clear(); zmqSs.str("");
    zmqSs << getpid();
    record.name = "/resolve/" + zmqSs.str() + "/control";
    record.pid = zmqSs.str();
    Resolve(record);
    zmqSs.clear(); zmqSs.str("");
    zmqSs << "tcp://" << record.host << ":" << record.port; 
    std::string zmqPortName = zmqSs.str(); 
    std::cout << "Bind to socket " << zmqPortName << std::endl; 
    cmd_socket->bind(zmqPortName.c_str());
  }
  
  {
    // incoming port, function as client
    zmqPortName = "/txt2morsemodule" + cliParam->module_id + "/txt";
    portTxtIn.name = zmqPortName;
    zmqPortName = "/resolve" + portTxtIn.name;
    pns_record record;
    record.name = zmqPortName;
    zmqSs.clear(); zmqSs.str("");
    zmqSs << getpid();
    record.pid = zmqSs.str();
    Resolve(record);
    zmqSs.str("");
    zmqSs << "tcp://" << record.host << ":" << record.port;
    zmqPortName = zmqSs.str();
    std::cout << "Bind to socket " << zmqPortName << std::endl;
    portTxtIn.sock->bind(zmqPortName.c_str());
  }
  {
    // outgoing port, function as server
    zmqPortName = "/txt2morsemodule" + cliParam->module_id + "/morse";
    portMorseOut.name = zmqPortName;
    zmqPortName = "/resolve" + portMorseOut.name;
    pns_record record;
    record.name = zmqPortName;
    zmqSs.clear(); zmqSs.str("");
    zmqSs << getpid();
    record.pid = zmqSs.str();
    Resolve(record);
  }
}

void Txt2MorseModule::readCommands() {
  while (true) {
    HandleCommand();
  }
}


void Txt2MorseModule::Resolve(pns_record & record) {
  std::cout << "Acquire TCP/IP port for " << record.name << std::endl;
  std::string reqname = record.name + ':' + record.pid;
  zmq::message_t request (reqname.size() + 1);
  memcpy ((void *) request.data (), reqname.c_str(), reqname.size());
  ns_socket->send(request);
  
  zmq::message_t reply;
  if (!ns_socket->recv (&reply)) return;
  size_t msg_size = reply.size();
  char* address = new char[msg_size+1];
  memcpy (address, (void *) reply.data(), msg_size);
  address[msg_size] = '\0';
  std::string json = std::string(address);
  std::cout << "Received " << json << std::endl;
  delete [] address;
  
  // get json object
  bool valid;
  json_spirit::Value value;
  if (!json_spirit::read(json, value)) {
    valid = false;
    std::cerr << "Not a json value" << std::endl;
    return;
  }
  if (value.type() != json_spirit::obj_type) {
    std::cerr << "[1] Unexpected object type "" << Value_type_str[value.type()] << """;
    std::cerr << " instead of "" << Value_type_str[json_spirit::obj_type] << """ << std::endl;
    return;
  }
  
  // a "json_spirit object" is - by default - a vector of json pairs
  json_spirit::Object obj = value.get_obj();
  
  for( json_spirit::Object::size_type i = 0; i != obj.size(); ++i ) {
    const json_spirit::Pair& pair = obj[i];
    const std::string& key = pair.name_;
    const json_spirit::Value& value = pair.value_;
    if (key == "identifier") {
      // same thing
    } else if (key == "server") {
      record.host = value.get_str();
    } else if (key == "port") {
      record.port = value.get_str();
    } else if (key == "pid") {
      record.pid = value.get_str();
    }
  }
}

void Txt2MorseModule::SendAck(zmq::socket_t *s, bool state) {
  if (debug) std::cout << "Send ACK" << std::endl;
  SendRequest(s, state, true, "ACK");
}

bool Txt2MorseModule::ReceiveAck(zmq::socket_t *s, bool & state, bool blocking) {
  int reply_size = 0;
  char *reply = GetReply(s, state, blocking, reply_size);
  if (reply == NULL) return false;
  std::string req = std::string(reply);
  delete [] reply;
  if (req.find("ACK") != std::string::npos) {
    if (debug) std::cout << "Got ACK, thanks!" << std::endl;
    return true;
  }
  std::cerr << "Error: got \"" << req << "\", no ACK, state compromised" << std::endl;
  return false;
}
  
char* Txt2MorseModule::GetReply(zmq::socket_t *s, bool & state, bool blocking, int & reply_size) {
  if (s == NULL)
    return NULL;
  zmq::message_t reply;
  char* result = NULL;
  reply_size = 0;
  try {
    if (blocking)
      state = s->recv(&reply);
    else
      state = s->recv(&reply, ZMQ_DONTWAIT);
  } catch (zmq::error_t &e) {
    std::cout << "Error: received zmq::error_t " << e.what() << std::endl;
  }
  if (state) {
    size_t msg_size = reply.size();
    result = new char[msg_size+1];
    memcpy (result, (void *) reply.data(), msg_size);
    result[msg_size] = '\0';
    reply_size = msg_size;
    //std::cout << "Result: \"" << std::string(result) << "\"" << std::endl;
  }
  return result;
}

void Txt2MorseModule::SendRequest(zmq::socket_t *s, bool & state, bool blocking, std::string str) {
  if (state) {
    zmq::message_t request(str.size());
    memcpy((void *) request.data(), str.c_str(), str.size());
    if (debug) std::cout << "Send request: " << str << std::endl;
    if (blocking)
      state = s->send(request);
    else
      state = s->send(request, ZMQ_DONTWAIT);
  } else {
    std::cout << "Send nothing (still waiting to receive) " << std::endl;
  }
}

void Txt2MorseModule::HandleCommand() {
  int reply_size = -1;
  bool state = false;
  char *reply = GetReply(cmd_socket, state, true, reply_size);
  if (reply == NULL) return;
  std::cout << "HandleCommand: " << std::string(reply, reply_size) << std::endl;
  if (reply_size < 2) std::cerr << "Error: Reply is not large for magic header + command string" << std::endl;
  char magic_value = reply[0];
  reply[reply_size-1] = '\0';
  if (magic_value == 0x01) { // connect to command...
    std::string name = std::string(reply+1);
    int pos = name.find("->");
    if (pos == std::string::npos) {
      std::cerr << "Error: no -> separator in connect command" << std::endl;
      return;
    }
    std::string source = name.substr(0, pos);
    std::string target = name.substr(pos+2); // todo: 
    std::cout << "Connect from " << source << " to " << target << std::endl;
    Connect(source, target);
  } else {
    std::cerr << "Error: Unknown command!" << std::endl;
  }
  SendAck(cmd_socket, true);
  delete [] reply;
}

void Txt2MorseModule::Connect(std::string source, std::string target) {
  pthread_mutex_lock(&cmdMutex);
  zmq::socket_t *s = GetSocket(source);
  if (s == NULL) {
    pthread_mutex_unlock(&cmdMutex);
    return;
  }
  pns_record t_record;
  t_record.name = "/resolve" + target;
  Resolve(t_record);
  std::stringstream ss; ss.clear(); ss.str("");
  ss << "tcp://" << t_record.host << ":" << t_record.port; 
  std::string sock = ss.str(); 
  std::cout << "Connect to socket " << sock << std::endl; 
  try {
    s->connect(sock.c_str());
  } catch (zmq::error_t &e) {
    std::cerr << "Error: Could not connect to " << target << ", because: " << e.what() << std::endl;
  }
  pthread_mutex_unlock(&cmdMutex);
}

zmq::socket_t* Txt2MorseModule::GetSocket(std::string name) {
  for (int i = 0; i < zmq_sockets.size(); ++i) {
    if (zmq_sockets[i]->name.find(name) != std::string::npos) return zmq_sockets[i]->sock;
  }
  std::cerr << "Error: socket name could not be found! " << name << std::endl;
  return NULL;
  //assert(false); // todo, get the previously registered socket by name
}

std::string* Txt2MorseModule::readTxt(bool blocking) {
  pthread_mutex_lock(&cmdMutex);
  int reply_size = -1;
  char *reply = GetReply(portTxtIn.sock, portTxtIn.ready, blocking, reply_size);
  if (!portTxtIn.ready) {
    delete [] reply;
    pthread_mutex_unlock(&cmdMutex);
    return NULL;
  }
  if (reply == NULL) {
    pthread_mutex_unlock(&cmdMutex);
    return NULL;
  }
  SendAck(portTxtIn.sock, portTxtIn.ready);
  pthread_mutex_unlock(&cmdMutex);
  if (reply_size < 1) std::cerr << "Error: Reply is not large enough to store a value!" << std::endl;
  portTxtValue = std::string(reply);
  delete [] reply;
  return &portTxtValue;
}

bool Txt2MorseModule::writeMorse(const std::string output) {
  std::stringstream ss; ss.clear(); ss.str("");
  ss << output; // very dirty, no endianness, etc, just use the stream operator itself
  pthread_mutex_lock(&cmdMutex);
  bool state = portMorseOut.ready;
  SendRequest(portMorseOut.sock, state, false, ss.str());
  if (state) portMorseOut.ready = false;
  if (!portMorseOut.ready) {
    bool ack_state = true;
    ReceiveAck(portMorseOut.sock, ack_state, true);
    if (ack_state) {
      portMorseOut.ready = true;
      pthread_mutex_unlock(&cmdMutex);
      return true;
    }
  }
  pthread_mutex_unlock(&cmdMutex);
  return false;
}

} // namespace
