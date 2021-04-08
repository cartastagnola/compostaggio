#!/bin/bash
SESSION=$USER

tmux -2 new-session -d -s $SESSION


tmux new-window -t $SESSION:1 -n 'Logs'
tmux split-window -h
tmux split-window -h
tmux split-window -v
tmux split-window -v


tmux select-pane -t 0
tmux resize-pane -L 100
tmux send-keys 'watch -n1 "cat /proc/cpuinfo | grep "MHz" | sort -r | head -32"' C-m

tmux select-pane -t 1
tmux resize-pane -L 100
tmux send-keys 'watch -n1 "cat /proc/cpuinfo | grep "MHz" | sort -r | tail -32"' C-m


tmux send-keys 'watch -n1 inxi -s' C-m


tmux select-pane -t 2
tmux resize-pane -U 50
tmux send-keys 'watch -n1 ${HOME}/bin/clean_sensors.sh' C-m


tmux select-pane -t 3
tmux send-keys 'watch -n1 rocm-smi' C-m

tmux select-pane -t 4
tmux resize-pane -U 7
tmux send-keys 'watch -n1 ${HOME}/bin/gpu_sensors.sh' C-m


# # Set default window
tmux select-window -t $SESSION:1

# Attach to session
tmux -2 attach-session -t $SESSION

