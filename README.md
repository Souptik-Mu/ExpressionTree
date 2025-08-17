# ExpressionTree
A multi-digit expression solver using c++ and binary tree(Supports brackets).

This uses a simple binary tree to store the expression.<br>
<p> A expression String can be passed in <code>Tree::LoadExpression()</code> that will parse the string into a list of tokens. This list of tokens are further used to build the expression tree by locating operator tokens and by checking their precedence.</p>
<br>
<p> Here tokens are the node of the tree. It contains a operator or a operand. I used <code>std::optional</code> though it not may be necessary. </p>
<p> I did completed this project almost a year ago, but it has few here there twiks to make. I used g++ to make this.<br> And it also have a nice graphical tree display.</p>

<h3> Here is a sample output </h3>

![image](https://github.com/user-attachments/assets/c2bf9226-65c0-4a48-905d-bf3f9b8d5271)
