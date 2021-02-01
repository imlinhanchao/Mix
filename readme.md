# 半透明混色算法實例

本項目演示了如何通過半透明混色算法將 PNG 圖片叠加在其他圖片上方。核心計算代碼可見 `Mix\MixDlg.cpp` 中的 `MixPicture` 函數。

基本混色算法公式：

```
color = (color1 * (MaxAlpha - alpha) + color2 * alpha) / MaxAlpha
```

需對 RGB 分別計算。