<h1  align="center"> MoneyTracker </h1>

<h2  align="center"> MoneyTracker is a C++ console application that allows you to track your income and expenses. </h2>
<br>


<h2  align="center"> How to use </h2>

>     mkdir build
>     cd build
>     cmake ..
>     make -j
>     .\MONEYTRACKER.exe (app)
>     .\MONEYTRACKER-ut.exe (tests)

<h3 align="center">  Registration&Login Menu </h3>

Data validation plays an important role in the registration and login process by ensuring that only valid data, or data that meets minimum requirements, is stored and used in the application. Using the **bcrypt library** to create password hashes increases the security of the application by preventing unauthorized access to user passwords.

Examples of hashed logins and passwords - stored in the config file:
```
User1: $2b$10$TTpZEazT.3ocHuI/fMgdP.KN/zM3ExKangGSZqv5wV1BOnsz42u/6;$2b$10$TTpZEazT.3ocHuI/fMgdP.om4vLOP.2DvGwzd1eSx8RbHxjY1wULq;
User2: $2b$10$3ISEmmRt5MeOaRJtobod8eHUf6/i1g1dzWl9E/0mdL5DePbkwJHAS;$2b$10$3ISEmmRt5MeOaRJtobod8edAZDAIyLtx/GBOdswupF3o7gkVplLwG;
```

<div align="center">
      <img src="https://user-images.githubusercontent.com/85802542/224577710-924a4138-f8e1-4c34-99be-c1fca567a2aa.gif" alt="LoginAndRegister3">
</div>
<br><br>
<h3 align="center">   Functionality</h3>

**Transaction Management**: Allows users to add new transactions, set a current transaction, print all transactions, and sort transactions by different styles. In addition, the application can display income and expenses in different ways and modify transaction data. Allows the user to remove a single transaction or delete all transactions at once.
<br>
<div align="center">
      <img src="https://user-images.githubusercontent.com/85802542/224577679-04aca325-9002-4f4e-9d53-598cc3848272.gif" alt="Functionality">
</div>
<br><br>
<h3 align="center">  Generating Excel File</h3>

Using the Libxlsxwriter library, we can generate summaries in an Excel file. By using appropriate functions, we can create pie charts, tables with data, and also cost summa!
ries. With the help of Libxlsxwriter, we can create professional-looking Excel files that can be used for a variety of purposes.

<div align="center"><img src="https://user-images.githubusercontent.com/85802542/225407337-7adfb7d3-2f7a-44f2-827b-224325ab20fa.gif" alt="ExcelFile" ></div>
<div align="center"><img src="https://user-images.githubusercontent.com/85802542/224513420-6005e0b8-098e-4f33-a0d8-aea4c5264e9b.png" alt="GeneratedExcelFile" width="30%"></div>

<br><br>

<h3 align="center">  Obligations Adding Functionality </h3>


This functionality allows users to add their financial obligations to the system, including loans and bills. Once added, the system will keep track of when the obligation is due, the amount owed, and any other relevant details. Users can also specify the pay date and for loans, the number of installment payments.

For bills, payments are due monthly. The system will automatically calculate the amount due each month based on the user's input. This feature helps users to budget and plan ahead for recurring expenses.

<div align="center"><img src="https://user-images.githubusercontent.com/85802542/225409780-b8317d47-4ad7-4f17-9c36-81ab491c1f39.gif" alt="Obligations" ></div>
