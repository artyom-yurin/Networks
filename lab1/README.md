# 1 LAB

### Specification
- parent process will be the server
- child process will be the client
- client accepts commands from user and sends them to server via pipes
- server stores actual data structure and invokes stack functions, printing the
result of each action

### Commands
- `create` - create a stack
- `push value` - push some integer value to the stack
- `pop` - pop last element from the stack
- `peek` - return the value of top element on the stack
- `empty` - return 1 if the stack is empty, otherwise 0
- `display` - print all elements from top to bottom
- `stack_size` - print current size of the stack
- `quit` - quit from application
- `help` - show commands list