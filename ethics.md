# Scenario 1: Responsible Reporting of Security Vulnerabilities

## A: Main Ethical question:
The main ethical question that I'd face in this scenario would be whether to prioritize the safety of the public by finding someway to let instaToonz know the vulnerability in their service, or to prioritize my own financial and legal wellbeing and to keep it a secret. instaToonz's hostile approach to dealing with security researchers, as seen in the previous case in which the they sued a bug reporter and called for an FBI investigation. There's a couple of ways this decision making progress could go for me which i will address later.

## B: Stakeholders and their rights

### Me
As the person who discovered the bug, I face risks to my legal and financial situation by exposing myself to hostile and retaliatory company and their legal team.

### Users of instaToonz
All of the users of instaToonz would be put at risk from the possibility of malicious individual finding the bug first, and exploiting it for their own benefit. Comprimising the users' privacy in the process

### instaToonz, the company
As the company that provides the service they have a responsibility to provide safety for their users, they have a right to not have their intellectual property violated

## C: Additional information missing from the scenario
It's important to mention how **Section 1201 of the Digital Millenium Copyright Act** would affect my approach. Supposing the bug involves encryption, under Section 1201(a)(3) I'd be in violation of the Digital Millenium Copyright Act, since it is not allowed to "decrypt an encrypted work, or otherwise to avoid, bypass, remove, deactivate, or impair a technological measure." In which case, if the bug involved encryption I'd have been breaking the law by finding said bug which would put me personally in much greater risk by reporting through any form of official channel. on the other hand, the act does not include encyrpted works, therefore I'd feel a lot safer about communicating the bug through some official channel if no encryption was involved.

## D: Possible Actions

### Anonymous Report
I could report the bug anonymously to instaToonz using a fake account or a vpn for staying private, not fearing any retaliation. However, instaToonz (like most companies) would likely not a take an anonymous report very seriously, also they could investigate to try and find out my identity somehow

### Report with a third party
I could report the bug to a security body or organization that would be willing to deal with the consequences of retaliation, would be free from said retaliation, or would be more likely to be taken seriously by instaToonz. In the meantime i get to dodge the retaliation from instaToonz. However, given instaToonz history with outsourced security reports this is still no guarantee that this will be taken seriously either. 

### Go public
This feels like it could be very bad, as it would put me in the direct line of retaliation from instaToonz, and it would endager many of the users of their service, since the bug would become public for malicious entities before the company was able to fix the bug. As a small benefit though, the more security mindful users would abandon the app for the next weeks until the issue was fixed

### Do nothing
Lastly, I could simply just not do anything. I could choose to preserve my own safety and not report the bug, in exchange for having a heavy contience due to all the users who will be left in a vulnerable position by the bug, and simply hope that an instaToonz security researcher finds the bug before someone else who would use it with malice, however this would be in violation of the **ACM Code of Ethics and Professional Conduct** by knowingly putting others and their privacy at risk. 

## E: Discuss ACM
There's a few excerpts of the **ACM Code of Ethics and Professional Conduct** that enter into play in this particular case, these being: 1.1, 1.2, and 1.6

### 1.1 Contribute to society and to human well-being, acknowledging that all people are stakeholders in computing
This principles applies since the bug threatens the many people whose privacy depends on the soundness of instaToonz and their safety measures. This should compel me and instaToonz to see to it that found issues are resolved

### 1.2 Avoid harm
This is a very important principle in this particular case, since it introduces a direct conflict between my rights as a stakeholder, and the public as stakeholders. Since by witholding the information I have on the bug, I'd be putting them in risk and violating the principle. However, If I carelessly reveal the bug I'd be putting myself in harms way and therefore also violating the principle

### 1.6 Respect privacy
This principle refers to the responsibilty that computing professionals have to protect the privacy of others. Knowing that this privacy is compromised and not acting accordingly would also put me at violation of this principle

## F: Recommended course of action
It's a hard to find a direct conclusion from examining **ACM** alone due to some of the conflict that principle 1.2 introduces. However, both principles 1.1 and 1.6 really push the balance towards prioritizing the general public as a stakeholder, especially when considering the scale of the damages if I abstain from taking taking action in this particular case. However, I'd still like to take precautions and safeguard my general well-being as well.

So I ended up deciding I'll carry forward the disclosure of the bug with a third party. It'll minimize the risk to myself while maximizing the chances that instaToonz will take the necessary actions to ensure the well being of their users. 

I'd write a report on the vulnerability as well as the steps necessary to be taken in order to exploited and the possbile scale of the damages if this bug were exploited by a malicious entity. Then I'd have to choose a  trust-worthy middle-man (third party) to disclose the bug to so they can communicati with instaToon. An agency like CISA for example, then I'd submit my careful report to them.

In the best case the agency will successfully work witn instaToonz's security team, promptly fixing the bug, and i remain anonymous. 
In the worst case instaToonz still tries to sue me for tampering with their software, however by having gone through an official third party, I'd be in a much better position to legally defend myself.
