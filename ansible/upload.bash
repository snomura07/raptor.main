#!/bin/bash

ansible-playbook -i inventory/hosts.yml playbook/sync_src.yml
