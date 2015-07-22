#!/bin/bash
eval $(ssh-agent)
ssh-add /home/wangfan/.ssh/ppdggh
./ipreport
