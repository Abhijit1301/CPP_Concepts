Attempting to write a program for the following rule:
Because comments are removed before the preprocessor stage, a macro cannot be used to form a comment and an unterminated C-style comment doesn't spill over from an #include'd file.

This example just doesn't work with following error:
fatal error C1071: unexpected end of file found in comment
