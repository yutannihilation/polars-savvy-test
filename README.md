# ⚠️This is not for use⚠️


``` r
library(p01ars)

df <- p01ars_dataframe(
  A = 1:5,
  fruits = c("banana", "banana", "apple", "apple", "banana"),
  B = 5:1,
  cars = c("beetle", "audi", "beetle", "beetle", "beetle")
)

df
```

    shape: (5, 4)
    ┌─────┬────────┬─────┬────────┐
    │ A   ┆ fruits ┆ B   ┆ cars   │
    │ --- ┆ ---    ┆ --- ┆ ---    │
    │ i32 ┆ str    ┆ i32 ┆ str    │
    ╞═════╪════════╪═════╪════════╡
    │ 1   ┆ banana ┆ 5   ┆ beetle │
    │ 2   ┆ banana ┆ 4   ┆ audi   │
    │ 3   ┆ apple  ┆ 3   ┆ beetle │
    │ 4   ┆ apple  ┆ 2   ┆ beetle │
    │ 5   ┆ banana ┆ 1   ┆ beetle │
    └─────┴────────┴─────┴────────┘
