# Simple Communication Scenarios

## Scenario 1
If Alice wants to send Bob a long message and preserve its confidentiality, then they should engage in a Diffie-Hellman key exchange procedure 
(given that AITM is impossible in this scenario) in order to settle on an encryption key for using AES. For the Diffie-Hellman key exchange Alice must generate a random value (x) and send and then must send Bob the two public values (g and p) along with her public key that she got using x, g, and p (g**xmodp).

Bob gets Alice's message and generates a random number of his own (y) and then
creates his own public key (g**ymodp), which he then sends to Alice. 
Once both Alice and Bob have each other's public keys, they can use their secret random values (x and y) to settle on a secret key. 

(g**xmodp)**ymodp = (g**ymodp)**xmodp

Then they can use this secret key to safely use AES encryption.


## Scenario 2
If Alice wants to send Bob a long message and she simply wants to protect its integrity (she doesn't mind if Mal sees it, but doesn't want Mal to be able to change it) then she could use a hash function on the data she sends Bob. SHA 256 would be a good and safe choice for this. Alice could use the command openssl dgst -sha256 (data) to generate a hash of the data she's sharing and that secure share that Hash with Bob (posting it on a secure website, showing it to him in person, sending it over email, etc...) which Bob could then compare with the hash he got after applying the same hash function to the data he received. Since good hash functions are sensitive to change in data, if the hash Bob calculated does not exactly match the one Alice showed him, then he'll know that the data has been tampered with.


## Scenario 3
If Alice wants to send Bob a long message (a contract) while prioritizing authenticity and confidentiality, then she would create a digital signature by hashing the contract data (H(data)) with for exambple sha 256, and encrypting it with the secret key of her key pair.The whole thing is her digital signature, Alice then concatinates it with the contract data, and encrypts it using bob's public key.

When Bob receives Alice's message, he can decrypt it using his secret key, which would yield the document plus Alice's digital signature. Bob can then use Alice's public key to decrypt the hash of her signature concatinated with. Bob can then perform his own hash function on the contract data, if the resulting hash matches the one in Alice's signature, then he can be certain that it was sent by Alice


# Questions about breaking security

## Scenario 4

### Claim 1: 
Alice could claim that an attacker performed a AITM attack and given Bob a false public key while convicing him that it was Alice he was talking to, while convincing Alice that Bob had indeed received her document. This would be very plausible since there's not CA involved in the trade of information, and it woulbe easily verifiable by looking at Alice's public key vs the one that Bob used when decrypting the data he received.

### Claim 2: 
Alice could also claim that an attacker somehow stole her secret key from her machine (either by hacking into her system or by physically having access to her device). With this secret key the attacker could easily pretend to be Alice and pass any information along as her. This is also plausible, but it wouldn't be very easy to verify unless Alice had some evidence of her key being stolen (camera footage of an intruder is an example).

### Claim 3: 
Lastly, Alice could claim that a Malware was installed by an attacker (or unknowingly by herself) on her computer that actively changed the contract she sent after she signed it, intercepting the file before it was sent, and changing both the document itself and the hash value it produced. I would also consider this to be very plausible.

## Scenario 5
The formula that the CA would use to compute sig\_Ca is the following
Sig\_ca = E(S\_ca, H(data)) where S stands for the CA's secret key, and H(data) is a hash of the key that Bob plus "bob.com"

## Scenario 6
No, it is not enough. Alice needs to produce a challenge for Bob, to which Bob must reply by signing it with his secret key and creating a digital signature, which Alice can verify using Bob's public key

## Scenario 7
How to subvert CA trust system?

### First Approach
Like Alice's second claim in scenario 4, an attacker could steal Bob's secret key (S\_Bob) and since his certifcate would be public that same attacker could pass Alice's challenge and successfully pretend to be Bob

## Second Approach
An attacker could somehow steal the signature of the certifiate authority, making Alice communicate with a false and or malicious website instead of Bob's.


