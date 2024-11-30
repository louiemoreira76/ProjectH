from openpyxl import Workbook
from win32com.client import Dispatch

workbook = Workbook()
sheet = workbook.active

sheet["A1"] = "Luis"
sheet["B2"] = "Okay i'am"

cell = sheet["B2"] 
cell.value = "I will realize my dreams!!!"
print(cell.value)

workbook.save(filename="teste_python.xlsx")
#abrir o aquirvo automaticamente#

x1 = Dispatch("Excel.Application")
x1.Visible = True

wb = x1.Workbooks.Open(r'C:\Users\£ui$\Documents\Python\teste_python.xlsx')
