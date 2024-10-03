#!/bin/bash
sh ./lowerMaxFreq.sh
likwid-perfctr -g ENERGY $1
sh ./restoreMaxFreq.sh
likwid-perfctr -g ENERGY $1
