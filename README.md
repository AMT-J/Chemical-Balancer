## 化学配平器
#### 1.本程序可实现化学、离子方程式的配平和检测是否配平
#### 2.下载地址 https://github.com/AMT-J/ChemistryCal/releases/tag/v5.2.0
#### 3.输入的化学方程式规则如下：

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
