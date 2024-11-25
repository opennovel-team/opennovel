# アニメ

OpenNovel の画面はレイヤで構成されており、それぞれのレイヤは位置、透過、拡大率、回転といった情報を持ちます。
これらの情報を時間経過で変化させる機能がアニメです。

## アニメスクリプト

アニメはアニメスクリプトというテキストファイルに記述され、[@anime](referene.html) コマンドで再生されます。
アニメファイルは `anime` フォルダに格納されます。

たとえば、メッセージボックスを1秒かけて右側に100pxずらすアニメファイルは、下記のようになります。
```
move {
    layer:  msg;
    start:  0.0;
    end:    1.0;
    from-x: +0;
    from-y: +0;
    from-a: 255;
    to-x:   +100;
    to-y:   +0;
    to-a:   255;
}
```

## レイヤの構成

レイヤは上から下の順に、下記の構成です。

```
text8
text7    (テキスト表示用)
text6
text5
text4
text3
text2
text1 

chf-lip  (キャラ顔の口パク)
chf-eye  (キャラ顔の目パチ)
chf      (キャラ顔)

name     (名前ボックス)
msg      (メッセージボックス)

effect4  (キャラの上のエフェクト)
effect3
effect2
effect1

chc-lip  (中央キャラの口パク)
chc-eye  (中央キャラの目パチ)
chc      (中央キャラ)
chrc-lip (右中キャラの口パク)
chrc-eye (右中キャラの目パチ)
chrc     (右中キャラ)
chr-lip  (右キャラの口パク)
chr-eye  (右キャラの目パチ)
chr      (右キャラ)
chlc-lip (左中キャラの口パク)
chlc-eye (左中キャラの目パチ)
chlc     (左中キャラ)
chl-lip  (左キャラの口パク)
chl-eye  (左キャラの目パチ)
chl      (左キャラ)
chb-lip  (背面キャラの口パク)
chb-eye  (背面キャラの目パチ)
chb      (背面キャラ)

effect8  (背景とキャラの間のエフェクト)
effect7
effect6
effect5

bg2      (背景2/スクロールループ用)
bg       (背景)</code></pre>
```

`effect1` から `effect8` は、雨のアニメーションや、色味を加えるのに使えます。

`text1` から `text8` は、`@text` 命令でテキストを描画するのに使えます。

## アニメでの拡大、縮小、回転

```
test1 {
    layer:  effect1;
 
    # 開始時刻と終了時刻
    start:  0.0;
    end:    3.0;

    # 開始時の座標と透明度
    from-x: 0;
    from-y: 400;
    from-a: 255;

    # 終了時の座標と透明度
    to-x:   0;
    to-y:   400;
    to-a:   255;

    # 画像内での拡大縮小・回転の中心座標
    center-x: 600;
    center-y: 100;

    # 拡大率 
    from-scale-x: 1.0;
    from-scale-y: 1.0;
    to-scale-x:   2.0;
    to-scale-y:   2.0;
 
    # 回転(プラスだと右回り、マイナスだと左回り)
    from-rotate:  0.0;
    to-rotate:    -360;
}
test2 {
    layer:  effect1;

    start:  3.0;
    end:    6.0;

    from-x: 0;
    from-y: 400;
    from-a: 255;

    to-x:   0;
    to-y:   400;
    to-a:   255;

    center-x: 600;
    center-y: 100;

    from-scale-x: 2.0;
    to-scale-x:   1.0;

    from-scale-y: 2.0;
    to-scale-y:   1.0;

    from-rotate: -360;
    to-rotate:   0;
}
```

## アニメのリセット

例えば、レイヤーを拡大するアニメファイルを用意したとき、拡大を元に戻すためにアニメファイルを用意するのは少し面倒です。
そこで用意されているのが `@anime reset` です。

下記のように `@anime reset` を利用することで、移動、拡大、回転の状態をリセットすることができます。

```
@anime reset layer-bg,xy,scale,rotate
@anime reset layer-chc,xy,scale,rotate
@anime reset layer-all,xy,scale,rotate
```

上記では、`layer-bg` だと背景、`layer-chc` だと立ち絵中央、`layer-all` だと全てのレイヤーをリセットし、アニメ前の状態に戻します。
`xy` は x 位置 と y 位置、`scale` は拡大率、`rotate` は回転をリセットすること表し、単体のみでも複数でも指定できます。

他の例として、下のように書くと、背景の拡大率のみをリセットすることが可能です。

```
@anime reset layer-bg,scale
```

## アニメのクリア

### 特定のレイヤーのアニメを強制終了するには

`@anime clear` コマンドに停止したいレイヤーを記述します。

```
@anime clear layer-bg,layer-chc
```

### すべてのアニメを強制終了するには

`@anime clear` コマンドに `layer-all` を記述します。

```
@anime clear layer-all</code></pre>
```
