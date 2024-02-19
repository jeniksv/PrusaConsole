#!/bin/sh

sudo cp cz.prusa3d.virtual-sla.conf /etc/dbus-1/system.d/cz.prusa3d.virtual-sla.conf
git submodule update --init --recursive
sh build_sim.sh
python3 -m venv venv
source venv/bin/activate
pip install -r requirements.txt
pip install pyyaml
pip install gpiod==1.5.4
sudo mkdir /run/model && sudo touch /run/model/sl1s
sh make_version.sh
PYTHONPATH=".:dependencies/Prusa-Error-Codes" PATH="${PATH}:." python3 -m slafw.virtual
