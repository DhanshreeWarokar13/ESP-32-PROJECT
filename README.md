# ESP-32-PROJECT
 Designed ATM machine using ESP32 on Ardino IDE and check the balance if is cash withdrawn or credited.
 #IDEA :
 Ultimately, we had to read a Google spreadsheet containing our username, password, and beginning account amount in order to log in to our accounts using the previously stored login information. I accomplished that using an Appscript function.After logging in, I've given the user the option to pick whether they want to see their balance, credit or debit their account, and the bot will act in accordance with their decision. If the user selects debit, he will be prompted to enter the amount to debit in multiples of 100. Once he enters the number of notes of 100, the bot will display the total amount debited and the account's remaining balance. This information will also be printed on the serial monitor and sent to separate Google Sheets.\\Similar events occur when we give the credit command. After we enter the command, the final balance after crediting and the amount credited in the account will be displayed on the serial monitor. Now because we are required to display all of our transactions on g.sheet and to update it often, we created a separate method called transactionto carry that enables us to save our output in g.sheet. We will be able to see this on g.sheet once the data has been stored.
