import pandas as pd
import matplotlib.pyplot as plt

fig, ax = plt.subplots(3, 1)

df = pd.read_csv("EUR_USD.csv", delimiter="\t")
print(df.shape)
ax[0].plot(df["index"], df['open'])
ax[0].plot(df["index"], df['closed'])
ax[0].set_title("EUR/USD")
ax[0].set_xlabel("Index")
ax[0].set_ylabel("Open/Close")


xf = pd.read_csv("gold.csv", delimiter="\t")
print(xf.shape)
ax[1].plot(xf["index"], xf['open'])
ax[1].plot(xf["index"], xf['closed'])
ax[1].set_title("Gold")
ax[1].set_xlabel("Index")
ax[1].set_ylabel("Open/Close")

nf = pd.read_csv("us500.csv", delimiter="\t")
print(xf.shape)
ax[2].plot(nf["index"], nf['open'])
ax[2].plot(nf["index"], nf['closed'])
ax[2].set_title("S&P 500")
ax[2].set_xlabel("Index")
ax[2].set_ylabel("Open/Close")
plt.show()




