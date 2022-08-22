# Gimmy Hashing algorithm
## Introduction
The gimmy algorithm is a hashing algorithm which takes advantage of the unpredictability of digits in the product of two numbers. First, however, it is important to cover a couple of important traits about multiplication.
### Right end principle
The first important trait of multiplication is that the last few digits of the product depend solely upon the last few digits of the multiplicands. The author refers to this as the "Right end principle" because he has not yet found the official name for it. This fact is fairly intuitive, but as a demonstration, here is an example:

| Product 1 | Product 2 | Product 3 | Product 4 |
|----------:|----------:|----------:|----------:|
| 000,000,**342** | 000,098,**342** | 000,000,**342** | 496734565734563**342** |
| &times; 000,000,**217** | &times; 000,001,**217** | &times; 000,017,**217** | &times; 960279773683570**217** |
| = | = | = | = |
| 000,074,**214** | 119,682,**214** | 005,888,**214** | 477004156364393019200457594091185**214** |

No matter what two numbers we multiply, as long as the last three digits are "342" and "217" in base 10, the last three digits of the product will be "214" in base 10. It is worth noting that while the principle holds true for all bases, the exact multiplicand-to-product matching will vary from one base to another. <br/>
It is also worth warning the reader that this algorithm focuses heavily on digits. Digits are not numbers, just symbols used to represent numbers. Manipulating digits to form a hashed value does not constitute "math" any more than manipulating letters of the alphabet or colors of the light spectrum. However, as symbols, digits can be used to convey information, making them a suitable medium for encryption. Lasly, because digits can be readily converted into numbers and vise versa, they allow for quasi-mathematical operations. The gimmy algorithm jumps back and forth between treating the input as a number and treating it as a string.<br/>
Because of the right end principle, it is possible to partially multiply pieces of numbers without knowing the whole.

| Pair 1 | Pair 2 |
|----------:|----------:|
| ...94 | ...4559 |
| &times; ...75 | &times; ...3721 |
| = | = |
| ...50 | ...4039 |

At this point, we can drop the ellipses if we adopt some new symbols to help us remember that we are only dealing with the right end of larger numbers. With no new symbols handy, we can simply underline out operators for now. Therefore, 94 <u>&times;</u> 75 = 50. We cannot yet assert that 50 <u>&div;</u> 75 = 94, however, because 75 <u>&times;</u> 78 also equals 50. There is a subset of numbers which give us the ability to go both ways, and that is the subject of the next section.

### The "Potential Prime Multiplication Completeness" principle

The author is also unaware of a name for this trait but needed a heading for the section. It has to do with an interesting charactersitic of the products of large primes (large meaning two or more digits in most bases). First, any large prime in base 10 will end in a 1, 3, 7 or a 9. Anything ending in 5 is divisible by 5, and anything ending in an even digit is divisible by 2, making it composite.<br/>

Second, the product of any two large primes in base 10 will also end in a 1, 3, 7 or a 9. Furthermore, it is impossible to tell, by the last digit of the product alone, what the last digit of each of the multiplicands is. If the last digit of the product is a 3, it could have come from the pairs (1 <u>&times;</u> 3), (3 <u>&times;</u> 1), (7 <u>&times;</u> 9) or (9 <u>&times;</u> 7). In effect, if we confine ourselves to last digits of potential prime numbers, for any last digit of a product and last digit of one multiplicand, there is one and only one digit that the other multiplicand can end with to make the equation work. We can state that 3 <u>&div;</u> 7 = 9 and 3 <u>&div;</u> 1 = 3.<br/>

Anyone who has tried to factor products of two primes one digit at a time from the right side has probably noticed that this trait carries on to the rest of the digits in the number. Suppose a friend told you that he had written down two prime numbers on a piece of paper (in base 10), which he has named "a" and "b" for lack of better terms. He divulges to you that the last digit of a is 3 and the last digit of b is 7. He multiplies the numbers together and tells you that the last digit of the product is a 1, which you already deduced. He then divulges that the second-to-rightmost digit of the product is 6. Based on the right end principle, the last two digits of the product (61) are determined solely by the last two digits of each of the multiplicands. You already have the rightmost digits of a and b, and you assume that knowing the second-to-rightmost digit of the product will help you narrow down the options for the second-to-rightmost digits of a and b to a limited number of pairs. You are correct! When dealing with potential primes, that limited number is 10 every time (in base 10). In this case the options are (3 <u>&times;</u> 87), (13 <u>&times;</u> 97), (23 <u>&times;</u> 7), (33 <u>&times;</u> 17), (43 <u>&times;</u> 27), (53 <u>&times;</u> 37), (63 <u>&times;</u> 47), (73 <u>&times;</u> 57), (83 <u>&times;</u> 67) and (93 <u>&times;</u> 77). Knowing the third-to-last digit of the product would not allow us to eliminate any of these pairs, and, if we tried to find the last three digits of a and b, we would have 100 pairs (not listed here) that satisfy the equation.

While this trait is no help in prime factorization, it gives us an important and interesting quality. When dealing with the right end of potential primes, we can state that for any multiplicand b and product p, there is one and only one other multiplicand a such that a <u>&times;</u> b = p. The reversible nature of these operations with potential primes, opens up possibilities for cryptography. If a is your plaintext and b is a shared key, then a <u>&times;</u> b = p gives us a ciphertext that can be decrypted by the key. However, the key in this case should ideally be as long as the plaintext. If the key is as long as the plaintext, we may as well be using a one-time-pad, and one-time pads are mathematically impossible to break with much simpler operations, so our new cipher does not contribute much to shared key cryptography.<br/>

We only care about this reversibility for a hashing algorithm because, for two right-ends "x" and "y", x <u>&div;</u> y behaves more erratically than x <u>&times;</u> y. We want to make sure that x <u>&div;</u> y always yields one result.

<br/>
<u>&times;</u>
<u>&div;</u>