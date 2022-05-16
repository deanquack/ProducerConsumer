# ProducerConsumer
#
# This program processes a number of requests and sends them to a "broker" buffer which holds 12 requests at a time. This broker is broken down into 4 human requests and 
# 8 robot requests. 
#
# There are 2 different producer/consumer request types. The producer types for the broker buffer is human and autonoumous/robot, and the consumer types are fast and 
# slow algorithms. The producer types create the requests that are being sent in via the threads. When the number of human requests and/or robot requests reaches 12 in
# the queue, the consumer must consume/delete the request types in the broker. 
# 
# 
#
#
#
