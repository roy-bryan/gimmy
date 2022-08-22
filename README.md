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

While this trait is no help in prime factorization, it gives us an important and interesting quality. When dealing with the right end of potential primes, we can state that for any multiplicand b and product p, there is one and only one other multiplicand a such that a <u>&times;</u> b = p. The reversible nature of these operations with potential primes opens up possibilities for cryptography. If a is your plaintext and b is a shared key, then a <u>&times;</u> b = p gives us a ciphertext that can be decrypted by the key. However, the key in this case should ideally be as long as the plaintext. If the key is as long as the plaintext, we may as well be using a one-time-pad, and one-time pads are mathematically impossible to break with much simpler operations, so our new cipher does not contribute much to shared key cryptography.<br/>

For a hashing algorithm, we only care about reversibility because, for two right-ends "x" and "y", x <u>&div;</u> y behaves more erratically than x <u>&times;</u> y. To use <u>&times;</u>, though, we want x <u>&div;</u> y to always yields one result. The other reason we should prefer <u>&times;</u> over <u>&times;</u> is that dividing gives us the potential to scale the result up. A hashed value is usually smaller than the original, but it may sometimes be bigger. If we multiply two numbers that are each two digits long, the result will never exceed 4 digits, but, unless the right-end of the multiplicand is a factor of the right-end of the product, simply adding leading zeros to both will often allow the other multiplicand to grow indefinitely. For example, 0,000,000,043 <u>&div;</u> 0,000,000,037 = 7,837,837,839.

## Setting up the gimmy algorithm

The second principle in the introduction is almost a hashing algorithm by itself, but we need to manage a couple more things. To start with, hashing algorithms are usually expected to take on number as an input, and our <u>&div;</u> operator works with two numbers. The first part of the gimmy program deals with splitting an input number into two right-ends, suitable for the operation. The second part of the program divides the right-ends, but also has to make sure that they are potential primes.

### Dividing right-ends

Chronologically, this part comes after splitting the input into two components, but it is the foundation of the algorithm and affects the decisions we make when doing the splitting, so it is discussed first. We already covered most of the mathematics. This part takes in two values, "b" and "p", and returns a value "a" using our new division operator. To make sure that we are working with potential primes, we want the last digit of each of our numbers to be a 1, 3, 7 or 9 when working in base 10. This can easily be accomplished by appending one of these digits to the right of each of our two inputs. Arbitrarily, we might append 7 to both. If we do this consistently, the last digit of "a" will always be 9. Since the 9 is consistent, it should be dropped before returning our final "a" value.<br/>
Up till now, this document has used base 10 for illustrations. However, using base 2 for the program allows us to manipulate the numbers using binary operators. Also, it eliminates the need to pick an arbitrary digit to append to our values, as all large primes in base two end with a 1.<br/>
Finally, we should note that x <u>&div;</u> y yields a very boring and predictable result when y is a factor of x. This should be taken into consideration when splitting the input number into components.

### Splitting the input

Before we can divide our right-ends, we need a consistent way to derive two right-ends (b and p) from one input variable, in such a way that, after a 1 is appended to the end of each, b is not a factor of p. The most obvious way to get two strings from one input string is to split the string in half ("10101110" becomes "1010" and "1110"). The first half will become our b variable, while the second half becomes p. Assigning them this way instead of the other way around ensures that be will never be half of p or less. This implicitly ensures it will never be a factor of p, unless they are equal (which we deal with later).<br/>
If the input number is odd, we share the middle bit (e.g. "1000110" becomes "1000" and "0110"). This creates some predictability which we have to handle later because "11001" and "110001" always hash to the same value this way.<br/>
Also, hashing algorithms ideally use all digits in such a way that changing any one digit completely changes the output. The right end principle dictates that changing a digit will only affect the digits to its left. Therefore, to make the rightmost digit the most volatile, we append a parity bit to the end of each string before handing it to the second part. "0111" becomes "0111**1**" while "1111" becomes "1111**0**". A change in any of the other bits will affect the parity bit, changing the entire outcome.<br/>
Lastly, to keep b and p from being equal, and to solve the problem of inputs like "11001" and "110001" hashing to the same value. We consider the overall number of bits used to represent the input value. If the length is an even number, we set the second to last bit of b to 1 and the second to last bit of p to 0. If the length is an even, we set the second to last bit of b to 0 and p's length bit becomes 1.

### Demonstration
Below is a demonstration of the gimmy algorithm being used to hash the number 75, which is represented as 1001011 in binary, to a 4-bit number.

| Step | Input | b | p | a |
|------|------:|--:|--:|--:|
| Split Input | 1001011 | 1001 | 1011 | |
| Append Length Bit | 1001010 | 1001-0 | 1011-1 | |
| Append Parity Bit | | **1001**-0-0 | **1011**-1-1 | |
| Append 1 to Convert<br/> To Possible Prime | | 100100-1 | 101111-1 | |
| Calculate <br/> a = p <u>&div;</u> b | | 1001001 | 1011111 | 1100111 |
| Drop Last Bit | | | | 110011 |
| Output Desired Number<br/> of Hashed Bits | | | | 0011 |
