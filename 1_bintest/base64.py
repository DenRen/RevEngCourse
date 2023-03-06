s = ''
for i in range(251, 256):
    # for j in range(256):
        # for k in range(256):
    s += f'{chr(i)}{chr(90)}{chr(90)}'

with open('base64_in_ag', 'w') as file:
    file.write(s)
                