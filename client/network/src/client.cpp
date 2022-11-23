#include "../include/client.h"

// ----------------------------- OpenVPNClient -------------------------------

void OpenVPNClient::execOpenVPN() {
    // TODO : запуск OpenVPN клиента и подключение его к запущенному OpenVPN серверу
}

void OpenVPNClient::runOpenVPN() {
    // TODO : запуск на сервере контейнера с OpenVPN сервером
}

void OpenVPNClient::stopOpenVPN()  {
    // TODO : остановка контейнера с OpenVPN сервером
}

// ----------------------------- Client -------------------------------

// ----- public -----

void Client::_onContext() {
    // TODO : назначить действие после установления соединения с сервером (сокрее всего вызвать asincWrite())
}

void Client::_asyncReadMsg() {
    // TODO : получить сообщение от сервера: конфиг для запуска OpenVPN Client или таймаут
}

void Client::_handleRead() {
    // TODO : привести полученное сообщение в удобный формат и обрабоать команду в inputAnalysis
}

void Client::_inputAnalysis() {
    // TODO : обработать сообщение, полученное от сервера (запустить дальнейшие процессы (если пришёл json)
    //        или возобновить подключение (если пришёл таймаут)
}

void Client::_asincWrite() {
    // TODO : запаковать VPNContext в json и отправить на сервер
}

// ----- public -----

void Client::setVPNContext(VPNContext) {
    // TODO : задать режим, в котором запустится VPN
}

void Client::connect() {
    // TODO : установить соединение с сервером и отправить серверу VPNContext
}