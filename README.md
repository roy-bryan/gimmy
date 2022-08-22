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

At this point, we can drop the ellipses if we adopt some new symbols to help us remember that we are only dealing with the right end of larger numbers. With no new symbols handy, we can simply underline out operators for now. Therefore, 94 <u>&times;</u> 75 = 50. We cannot yet assert that 50 <u>&div;</u> 75 = 94, however, because 75 <u>&times;</u> 78 also equals 50.

<br/>
<u>&times;</u>
<u>&div;</u>