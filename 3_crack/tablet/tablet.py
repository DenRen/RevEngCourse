with open('source', 'rb') as source:
    bin = source.read()
    with open('cracked', 'wb') as cracked:
        cracked.write(bin.replace(
            b'\xe1\xfe\xff\x54',
            b'\x1f\x20\x03\xd5'
        ))
        