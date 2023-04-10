CC 				= gcc
.PHONY: master slave client_time client_txnum

master: master/master.c master/semisync_sender.c master/async_sender.c network/udp/udp_server.c network/udp/udp_client.c utils/config.c
	$(CC) -o build/master -pthread master/master.c master/semisync_sender.c master/async_sender.c network/udp/udp_server.c network/udp/udp_client.c utils/config.c -DREPLICATION=SEMISYNC -DNONCOOP -DSLAVE_NODE_NUM=2

slave: slave/slave.c slave/semisync_reciever.c slave/async_reciever.c network/udp/udp_server.c network/udp/udp_client.c utils/config.c
	$(CC) -o build/slave -pthread slave/slave.c slave/semisync_reciever.c slave/async_reciever.c network/udp/udp_server.c network/udp/udp_client.c utils/config.c -DREPLICATION=SEMISYNC -DNONCOOP -DSLAVE_NODE_NUM=2