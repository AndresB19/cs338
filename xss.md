# Cookies and Cross-Site Scripting

## Part 1: Cookies

a. Yes there are cookies in this domain, one to be precise (on firefox). It is called theme.

b. It did change, and the cookie also changed it 'value' header to red (in my case)

c. I didn't see a 'set cookie header' but I did see the 'Cookie' header that includes the 'theme' value which is set to 'default' at first and then 'red'

d. The theme I had selected is still selected

e. The my browser sends the cookie to the FDF server along with its GET requests.

f. The following from host to server: GET /fdf/?theme=red HTTP/1.1

g. Clicking on the value section of the cookie and editing it to be one of the values available (default, red, or blue).

h. Change the value in the original GET request, meaning the theme value so that it affects the whole interaction going forward.

i. Apparently firefox stores its cookies in a file named cookies.sqlite, in the '/.mozilla/firefox' directory

## Part 2: Cross-Site Scripting (XSS)

a. There are three types of XSS attacks. There is Reflected XSS (AKA Non-Persistent or Type I), Stored XSS (AKA Persistent or type II), and DOM Based XSS (AKA Type-0). Here's a link detailing them: https://owasp.org/www-community/Types_of_Cross-Site_Scripting

b. Moriarty made a post that contained malicious script into the fdf forum. The fdf forum then (and without proper validation) saves the malicious script or html into its database. Later, a user (Alice, Bob, Eve, or even Mal) logs into the forum and their browser requests the page for the post that Moriarty made (making a GET request). The forum sends the browser what it was queried for (even the malicious script/html), so the browser reads and loads what it was sent without having anyways of knowing what is malicious and what isn't. 

c. An attacker could modify the forum's body with html into a message that says that the user's session has timed out, and that they need to re-enter their username and password which they get through a script. Since it is coming from the same website, the user would trust this and enter their credentials which the script could be written to deliver to anywhere the attacker has access to it.

d. An attacker inserts a script into the forum that triggers the making of another post from the user's side (since the script has access to the user's session cookie through the browser). This new post (pre-made by the attacker) could be one in which the user admits to doing embarassing and/or criminal things that would blemish their reputation even though they didn't make this post themselves.

e. The user could never any type of command or script as is when input by a user, specifically finding the flags that signal the text is some sort script/html text, and representing them as normal text (as in like a string) instead of taking whatever any user uploads to the server at face value
