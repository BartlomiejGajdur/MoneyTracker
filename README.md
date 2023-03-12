<h1  align="center"> MoneyTracker </h1>

<h2  align="center"> MoneyTracker is a C++ console application that allows you to track your income and expenses. </h2>
<br><br>
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
![GeneratedExcelFile](https://user-images.githubusercontent.com/85802542/224513420-6005e0b8-098e-4f33-a0d8-aea4c5264e9b.png)
