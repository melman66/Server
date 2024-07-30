
function addClientToList(name)
{
    clients_list_model.append({"client" : name})
}

function addMessageToList(message)
{
    server_list_model_messages.append({"message" : message})
}

function addMsgNewClient(name)
{
    server_list_model_messages.append({"message" : "New client: " + name})
}

function changeServerState(state)
{
    serverIsStarted = state
}

function removeClientFromList(name)
{
    clients_list_model.remove(name)
}

function removeMsgClient(name)
{
    if (serverIsStarted) {
        server_list_model_messages.append({"message" : "Client disconnected: " + name})
    }
}

function sendMsgToClient(message)
{
    if (server_view.sendMsgToClient(selectedClient, message)) {
        server_input_message.input_message_text.text = ""
        server_view.messageSended(
                    server_view.getCurrentDateTime()+"\n"
                    +"Me:\n"+message)
    }
    else {
        server_view.messageSended("Error!!! Message is not sended! Please, check the selected reciver.")
    }
}

function setErrorFlag(err)
{
    error_flag = true
}

function startServer()
{
    if(error_flag) {
        error_flag = false
        return
    }

    if (!serverIsStarted){
        server_view.startServer(server_input_text_port.server_string_port);
    }
    else {
        server_view.stopServer();
    }
    return serverIsStarted
}

