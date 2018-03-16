#pragma once

#include "shvnodeitem.h"


#include <map>

namespace shv { namespace chainpack { class RpcMessage; } }
namespace shv { namespace iotqt { namespace rpc { class ClientConnection; } } }

class ShvBrokerNodeItem : public QObject, public ShvNodeItem
{
	Q_OBJECT
private:
	using Super = ShvNodeItem;
public:
	enum class OpenStatus {Invalid = 0, Disconnected, Connecting, Connected};
public:
	explicit ShvBrokerNodeItem(const std::string &server_name);
	~ShvBrokerNodeItem() Q_DECL_OVERRIDE;

	QVariant data(int role = Qt::UserRole + 1) const Q_DECL_OVERRIDE;

	OpenStatus openStatus() const {return m_openStatus;}

	void open();
	void close();
	//QString connectionErrorString();

	QVariantMap serverProperties() const;
	void setServerProperties(const QVariantMap &props);

	shv::iotqt::rpc::ClientConnection *clientConnection();

	unsigned requestLoadChildren(const std::string &path);

	ShvNodeItem *findNode(const std::string &path, std::string *path_rest = nullptr);
private:
	void onRpcMessageReceived(const shv::chainpack::RpcMessage &msg);
private:
	int m_oid = 0;
	std::string m_serverName;
	shv::iotqt::rpc::ClientConnection *m_clientConnection = nullptr;
	OpenStatus m_openStatus = OpenStatus::Disconnected;
	struct RpcRequestInfo;
	std::map<unsigned, RpcRequestInfo> m_runningRpcRequests;
};
