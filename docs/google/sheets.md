
# GOOGLE SHEETS

It reads:

if any **column** in `Transactions!C3:C100`  contains `Training Fees`, **SUM** the equivalent column in `Transactions!D3:D100`

```js
=sumif(Transactions!C3:C100, "Training Fees", Transactions!D3:D100)
```
<div class='grid' markdown>
<figure markdown='span'>
![alt text](img/image.png)
</figure>

<figure markdown='span'>
![alt text](img/image-1.png){width=310px}
</figure>

</div>
