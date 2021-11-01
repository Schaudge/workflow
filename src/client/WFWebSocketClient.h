/*
  Copyright (c) 2021 Sogou, Inc.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

  Author: Li Yingxin (liyingxin@sogou-inc.com)
*/

#ifndef _WFWEBSOCKETCLIENT_H_
#define _WFWEBSOCKETCLIENT_H_

#include <string>
#include <pthread.h>
#include <functional>
#include "HttpUtil.h"
#include "WFChannel.h"
#include "WebSocketMessage.h"

struct WFWebSocketParams
{
	int idle_timeout;
	int ping_interval;
	size_t size_limit;
	bool random_masking_key;
};

static constexpr struct WFWebSocketParams WEBSOCKET_PARAMS_DEFAULT =
{
	.idle_timeout		=	WS_HANDSHAKE_TIMEOUT,
	.ping_interval		=	-1,
	.size_limit			=	(size_t)-1,
	.random_masking_key	=	false,
};

class WebSocketClient
{
public:
	int init(const std::string& url);
	WFWebSocketTask *create_websocket_task(websocket_callback_t cb);
	WFWebSocketTask *create_ping_task(websocket_callback_t cb);
	WFWebSocketTask *create_close_task(websocket_callback_t cb);
	void deinit();

private:
	ComplexWebSocketChannel channel;
	struct WFWebSocketParams params;
	pthread_cond_t shutdown_cond;

public:
	WebSocketClient(const struct WFWebSocketParams *params,
					websocket_process_t process);
	WebSocketClient(websocket_process_t process) :
		WebSocketClient(&WEBSOCKET_PARAMS_DEFAULT, std::move(process))
	{ }
};

#endif
