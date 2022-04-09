English | [中文](README-cn.md)  
## Chemical Balancer
#### 1.This program can realize the balance of chemical and ionic equations and check whether they are balanced
#### 2.Download address https://github.com/AMT-J/Chemical-Balancer/releases/tag/v5.2.0
#### 3.The rules for entering chemical equations are as follows:

```
  <equation> ::= <expr> "=" <expr>
  <expr> ::= <coef> <formula> | <expr> "+" <coef> <formula>
  <coef> ::= <digits> | "" | <electron>
  <electron>::= "<"<digits>"+>" | "<"<digits>"->" | ""
  <digits> ::= {<digit>} 
  <digit> ::= "0" | "1" | ... | "9"
  <formula> ::= <term> <coef> | <formula> <term> <coef>
  <term> ::= <element> | "(" <formula> ")" |  "[" <formula> "]"
  <element> ::= <uppercase> | <uppercase> <lowercase>
  <uppercase> ::= "A" | "B" | ... | "Z"
  <lowercase> ::= "a" | "b" | ... | "z"
```
