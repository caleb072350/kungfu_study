/**
 * PageProvider
 * implements IPageProvider, diverge to different usage.
*/
#include "PageProvider.h"
#include "PageCommStruct.h"
#include "PageSocketStruct.h"
#include "PageUtil.h"
#include "Page.h"
#include "StrategySocketHandler.h"

#include <boost/asio.hpp>
#include <boost/array.hpp>

USING_YJJ_NAMESPACE

typedef boost::array<char, SOCKET_MESSAGE_MAX_LENGTH> SocketMArray;

/** get socket response via paged_socket */
void getSocketRsp(SocketMArray &input, SocketMArray &output)
{
    using namespace boost::asio;
    io_service io_service;
    local::stream_protocol::socket socket(io_service);
    socket.connect(local::stream_protocol::endpoint(PAGED_SOCKET_FILE));
    boost::system::error_code error;
    write(socket, buffer(input), error);
    socket.read_some(buffer(output), error);
}

/** send req via socket and get response in data */
void getSocketRspOnReq(PagedSocketRequest& req, SocketMArray& data, const string& name)
{
    memcpy(req.name, name.c_str(), name.length() + 1);
    SocketMArray reqBuf;
    memcpy(&reqBuf[0], &req, sizeof(req));
    getSocketRsp(reqBuf, data);
}

ClientPageProvider::ClientPageProvider(const string& clientName, bool isWriting, bool reviseAllowed):
    client_name(clientName), comm_buffer(nullptr)
{
    is_writer = isWriting;
    revise_allowed = is_writer || reviseAllowed;
    register_client();
}

void ClientPageProvider::register_client()
{
    PagedSocketRequest req = {};
    req.type = is_writer ? PAGED_SOCKET_WRITER_REGISTER : PAGED_SOCKET_READER_REGISTER;
    req.pid = getpid();
    SocketMArray rspArray;
    getSocketRspOnReq(req, rspArray, client_name);
    PagedSocketRspClient* rsp = (PagedSocketRspClient*)(&rspArray[0]);
    hash_code = rsp->hash_code;
    if (rsp->type == req.type && rsp->success)
    {
        comm_buffer = PageUtil::LoadPageBuffer(string(rsp->comm_file), rsp->file_size, true, false /*server lock this already*/);
    }
    else
    {
        throw std::runtime_error("cannot register client: " + client_name);
    }
}

void ClientPageProvider::exit_client()
{
    // send message to say good bye
    PagedSocketRequest req = {};
    req.type = PAGED_SOCKET_CLIENT_EXIT;
    req.hash_code = hash_code;
    SocketMArray rspArray;
    getSocketRspOnReq(req, rspArray, client_name);
}

LocalPageProvider::LocalPageProvider(bool isWriting, bool reviseAllowed)
{
    is_writer = isWriting;
    revise_allowed = is_writer || reviseAllowed;
}

PagePtr LocalPageProvider::getPage(const string &dir, const string &jname, int serviceIdx, short pageNum)
{
    return Page::load(dir, jname, pageNum, is_writer, false);
}

void LocalPageProvider::releasePage(void* buffer, int size, int serviceIdx)
{
    PageUtil::ReleasePageBuffer(buffer, size, false);
}