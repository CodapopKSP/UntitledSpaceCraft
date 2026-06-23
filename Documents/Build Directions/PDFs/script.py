import fitz

doc = fitz.open("combined.pdf")
total = len(doc)

for i, page in enumerate(doc):
    if i == 0:
        continue  # Skip cover page

    text = f"{i}"  # Page 2 gets number "1"

    rect = page.rect
    page.insert_textbox(
        fitz.Rect(0, rect.height - 29, rect.width, rect.height - 12),
        text,
        fontsize=10,
        align=fitz.TEXT_ALIGN_CENTER,
        color=(0, 0, 0),
    )

doc.save("numbered.pdf", garbage=4, deflate=True)
doc.close()