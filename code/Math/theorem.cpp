/*
Lucas's Theorem
	For non-negative integer n,m and prime P,
	C(m,n) mod P = C(m/M,n/M) * C(m%M,n%M) mod P
	= mult_i ( C(m_i,n_i) )
	where m_i is the i-th digit of m in base P.
-------------------------------------------------------
Kirchhoff's theorem
  A_{ii} = deg(i), A_{ij} = (i,j) \in E ? -1 : 0
  Deleting any one row, one column, and cal the det(A)
-------------------------------------------------------
Nth Catalan recursive function:
C_0 = 1, C_{n+1} = C_n * 2(2n + 1)/(n+2)
-------------------------------------------------------
Mobius Formula
u(n) = 1        , if n = 1
       (-1)^m   , 若 n 無平方數因數，且 n = p1*p2*p3*...*pk
       0        , 若 n 有大於 1 的平方數因數
- Property
1. (積性函數) u(a)u(b) = u(ab)
2. ∑_{d|n} u(d) = [n == 1]
-------------------------------------------------------
Mobius Inversion Formula
if      f(n) = ∑_{d|n} g(d)
then    g(n) = ∑_{d|n} u(n/d)f(d)
             = ∑_{d|n} u(d)f(n/d)
- Application
the number/power of gcd(i, j) = k
- Trick
分塊, O(sqrt(n))
-------------------------------------------------------
Chinese Remainder Theorem (m_i 兩兩互質)

  x = a_1 (mod m_1)
  x = a_2 (mod m_2)
  ....
  x = a_i (mod m_i)

construct a solution:

  Let M = m_1 * m_2 * m_3 * ... * m_n
  Let M_i = M / m_i

  t_i = 1 / M_i
  t_i * M_i = 1 (mod m_i)

  solution x = a_1 * t_1 * M_1 + a_2 * t_2 * M_2 + ... + a_n * t_n * M_n + k * M
  = k*M + ∑ a_i * t_i * M_i, k is positive integer.

  under mod M, there is one solution x = ∑ a_i * t_i * M_i
-------------------------------------------------------
Burnside's lemma
|G| * |X/G|  = sum( |X^g| ) where g in G
總方法數: 每一種旋轉下不動點的個數總和 除以 旋轉的方法數
-------------------------------------------------------
Lagrange multiplier
f(x,y) 求極值。必須滿足 g(x,y) = 0。

湊得 f(x,y) = f(x,y) + λ g(x,y)
定義 s(x,y,λ) = f(x,y) + λ g(x,y)

f(x,y) 的極值，等同 s(x,y,λ) = f(x,y) + λ g(x,y) 的極值。
欲求極值：
對 x 偏微分，讓斜率是 0。
對 y 偏微分，讓斜率是 0。

不管 λ 如何變化，λ g(x,y) 都是零，s(x,y,λ) 永遠不變。
欲求永遠不變的地方：
對 λ 偏微分，讓斜率是 0。

三道偏微分方程式聯立之後，其解涵蓋了（不全是）所有符合約束條件的極值。
{ ∂/∂x s(x,y,λ) = 0
{ ∂/∂y s(x,y,λ) = 0
{ ∂/∂λ s(x,y,λ) = 0
-------------------------------------------------------
Baby Step Giant Step
Get a^x = b (mod n)
x = im - j, m = ceil(sqrt(n))
a^im = b*a^j(mod n)
預處理 a^im, 1 <= i <= m， 存hash/map
接著去試從 0 <= j <= m有沒有a^im = b*a^j，有的話答案是 im-j。
可能需要特判 if b =1 then x= 0
*/
