<h1 align="center">Chemical Balancer</h1>
<p align="center">
  <a>English</a> |
  <a href="./README-cn.md">中文</a> 
</p>
<p align="center">
  <img src="https://img.shields.io/badge/Qt-%23217346.svg?style=for-the-badge&logo=Qt&logoColor=white" />
  <img src="https://img.shields.io/badge/Visual%20Studio-5C2D91.svg?style=for-the-badge&logo=visual-studio&logoColor=white" />
  <img src="https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white" />
  <img src="https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white" />
  <img src="https://img.shields.io/github/license/Ileriayo/markdown-badges?style=for-the-badge" />
</p>

## Introduction

 - This program can realize the balance of chemical and ionic equations and check whether they are balanced
 - The rules for entering chemical equations are as follows:

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
## Apply
 - [Download](https://github.com/AMT-J/Chemical-Balancer/releases/tag/v5.2.0)
