CC 				= gcc
.PHONY: master slave client_time client_txnum

master: master/master.c master/semisync_sender.c master/async_sender.c network/udp/udp_server.c network/udp/udp_client.c utils/config.c utils/timer.c log/tx_log.c
	$(CC) -o build/master_semisync_noncoop_slavenode1 -pthread master/master.c master/semisync_sender.c master/async_sender.c network/udp/udp_server.c network/udp/udp_client.c utils/config.c utils/timer.c log/tx_log.c -DREPLICATION=SEMISYNC -DNONCOOP -DSLAVE_NODE_NUM=1

slave: slave/slave.c slave/semisync_reciever.c slave/async_reciever.c network/udp/udp_server.c network/udp/udp_client.c utils/config.c log/tx_log.c
	$(CC) -o build/slave_semisync_noncoop_slavenode1 -pthread slave/slave.c slave/semisync_reciever.c slave/async_reciever.c network/udp/udp_server.c network/udp/udp_client.c utils/config.c log/tx_log.c -DREPLICATION=SEMISYNC -DNONCOOP -DSLAVE_NODE_NUM=1