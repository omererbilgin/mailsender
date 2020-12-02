# Smtp request example from google / By Omer Erbilgin

import smtplib
import sys

from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText

sender = " " #the email address which the mail is going to come from
sendingto = sys.argv[1] 

msg = MIMEMultipart('alternative')
msg['Subject'] = "Example Subject"
msg['From'] = sender
msg['To'] = sendingto

text = ""
html = """\
<head>
example html
<head>
"""

part1 = MIMEText(text, 'plain')
part2 = MIMEText(html, 'html')
msg.attach(part1)
msg.attach(part2)

mail = smtplib.SMTP('smtp.gmail.com', 587)

mail.ehlo()

mail.starttls()

mail.login('user', 'password') #login credentials for your gmail address
mail.sendmail(sender, sendingto, msg.as_string())
print('Mail sent to',sendingto)

mail.quit()
