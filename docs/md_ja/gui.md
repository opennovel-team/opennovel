GUIの作り方
==========

OpenNovel のGUI とは、タイトルメニュー画面やシステム UI を設計するための機能です。
GUI は 1 枚のメニュー画面であり、複数のボタンから構成されます。

ここではタイトルメニュー画面を例に説明しています。

## タイトルメニュー画面の作り方

### まずはじめに

サンプルゲームの中身を見ていきましょう。

### タイトル画面の呼び出し箇所

`txt/init.txt` の中で、`@gui title.txt` と書いてある行を探してみてください。
これがタイトルメニュー画面の呼び出し箇所です。
タイトルメニュー画面はGUI機能を使って実現されています。

`title.txt` というのは、`gui/` フォルダに入っている `title.txt` のことです。
このファイルは GUI ファイルと呼ばれています。

### GUI ファイル の中身

`gui/title.txt` ファイルを開いてみてください。
まず先頭に、下記のように書かれています。

```
# このファイルの基本設定
global {
    # 下記の画像を使用する
    base:   title/idle.png;
    idle:   title/idle.png;
    hover:  title/hover.png;
    active: title/hover.png;

    # フェードイン時間(秒)
    fadein: 0.2;

    # フェードアウト時間(秒)
    fadeout: 0.2;
}
```

この記述はGUIファイルの設定で、それぞれの指定の意味は下記のとおりです。

|指定名         |意味                                                                                                                                                         |
|---------------|-------------------------------------------------------------------------------------------------------------------------------------------------------------|
|base:          |一番下の背景となるレイヤーの指定。この base: を指定しなければゲームのステージ（背景、キャラ）が表示される。base: に画像ファイルを指定すると画像が表示される。|
|idle:          |ボタンがマウスでポイントされていないときに、ボタンの領域に表示する画像。                                                                                     |
|hover:         |ボタンがマウスでポイントされた時に、ボタンの領域に表示する画像。                                                                                             |
|active:        |スライダーのノブやトグルボタンで利用する画像。単純なタイトル画面では使いませんので、idleやhoverと同じ画像を指定すればよいです。                              |
|fadein:        |フェードイン時間(秒)。                                                                                                                                       |
|fadeout:       |フェードアウト時間(秒)。                                                                                                                                     |
|clickcancel:   |ボタン以外の箇所をクリックされた場合にGUIをキャンセルするか。                                                                                                |
|escapecancel:  |Escキーが押された場合にGUIをキャンセルするか。                                                                                                               |
|cancelse:      |キャンセル時のSEファイル。                                                                                                                                   |
|saveslots:     |1画面あたりのセーブデータ表示数。セーブ画面とロード画面で使用。                                                                                              |
|historyslots:  |1画面あたりのヒストリ表示数。ヒストリ画面で使用。                                                                                                            |

### ボタン画像の準備について

* 他のエンジンと違って、個々の小さなボタンの画像を使いません
* 代わりに、画面全体の中にボタンを配置した画像を利用します
* このデータを作るには、画像編集ソフトやペイントソフトのレイヤー機能を使います

### title.txt ファイルの構造

`title.txt` ファイルの続きについて見ていきます。
大まかに見ると3つのボタンについて書かれています。
遠目に眺めてみると、次の構造になっていることがわかります。

```
START {
    ...
}

LOAD {
    ....
}

CONFIG {
    ...
}
```

### START ボタンの中身

ここで START ボタンの中をよく見ていきます。

```
# STARTボタン
START {
    # 種類:ラベルへジャンプ
    type: goto;

    # ジャンプ先のラベル
    label: START;

    # 座標とサイズ
    x: 2;
    y: 495;
    width: 314;
    height: 192;

    # ポイントされたときの効果音
    pointse: btn-change.ogg;

    # クリックされたときの効果音
    clickse: click.ogg;
}
```

わかる部分、わからない部分があると思います。さらに詳しく見ていきましょう。

### クリックされたらラベルへジャンプ

`type: goto;` というのは、このボタンが押されたときに、「実行中のシナリオファイルどこかのラベルにジャンプする」、という意味です。
ラベルというのは、シナリオの中で、`:` から始まる行のことです。

`label: START;` というのは、このボタンが押されたときに、「シナリオファイルの `:START` という行にジャンプする」、という意味です。

### 座標とサイズ

座標とサイズですが、これは <code>Photoshop</code> や <code>CLIP STUDIO PAINT</code> などのツールで、
ボタンの位置とサイズを確認して書いてください。

### これでOK

たったこれだけです。意外と難しくなかった、という感想を持たれたと思います。

## ボタンを増やすには？

* START { ... } のブロックをコピーして、新しいブロックを作ってみましょう
* コピー先の START の部分には自分で新しい名前を付けてください
* アルファベットならなんでもいいです。(実を言うとSTARTが2つあってもそのまま動きます)

## ボタンの種類

|記述                            |意味                                                                                                                                        |
|--------------------------------|--------------------------------------------------------------------------------------------------------------------------------------------|
|type: goto;                     |押されるとラベルにジャンプします。ラベルは label: で指定します。                                                                            |
|type: gui;                      |押されると GUI にジャンプするボタンです。GUIは file: で指定します。                                                                         |
|type: gallery;                  |変数が 0 でない場合のみ表示され、押されるとラベルにジャンプするボタンです。変数は var: で指定し、ラベルは label: で指定します。             |
|type: mastervol;                |マスター音量のスライダーです。                                                                                                              |
|type: bgmvol;                   |BGM音量のスライダーです。                                                                                                                   |
|type: sevol;                    |SE音量のスライダーです。                                                                                                                    |
|type: charactervol;             |キャラクタ音量のスライダーです。index: でキャラクタ番号を指定します。                                                                       |
|type: textspeed;                |テキストスピードのスライダーです。                                                                                                          |
|type: autospeed;                |オートモードスピードのスライダーです。                                                                                                      |
|type: preview;                  |テキストのプレビュー領域です。                                                                                                              |
|type: fullscreen;               |フルスクリーン移行のボタンです。                                                                                                            |
|type: window;                   |ウィンドウ移行のボタンです。                                                                                                                |
|type: font;                     |デフォルトフォントを変更するボタンです。file: でフォントファイルを指定します。                                                              |
|type: default;                  |設定をデフォルトに戻すボタンです。                                                                                                          |
|type: savepage;                 |セーブデータのページ番号のボタンです。index: でページ番号を指定します。                                                                     |
|type: save;                     |セーブデータのボタンです。index: でページ内のスロット番号を指定します。                                                                     |
|type: load;                     |ロードデータのボタンです。index: でページ内のスロット番号を指定します。                                                                     |
|type: auto;                     |押されるとオートモードに移行するボタンです。                                                                                                |
|type: skip;                     |押されるとスキップモードに移行するボタンです。                                                                                              |
|type: title;                    |押されるとタイトル画面に戻るボタンです。                                                                                                    |
|type: history;                  |押されるとヒストリ表示に移行するボタンです。                                                                                                |
|type: historyscroll;            |ヒストリ表示の縦スクロールのスライダーです。                                                                                                |
|type: historyscroll-horizontal; |ヒストリ表示の横スクロールのスライダーです。                                                                                                |
|type: cancel;                   |GUIをキャンセルするボタンです。                                                                                                             |
|type: quit;                     |ゲームを終了するボタンです。                                                                                                                |
|type: namevar;                  |名前入力画面で利用する名前変数表示の領域です。namevar: で名前変数の文字(a-z)を指定します。                                                  |
|type: char;                     |名前入力画面で利用する文字入力ボタンです。msg: で入力する文字列を指定します。msg: には [clear], [backspace], [ok] の特殊文字も指定できます。|
|type: wms;                      |押されるとWMSを実行するボタンです。file: でWMSファイルを指定します。                                                                        |

## ボタンのオプション

|記述                  |意味                                                                   |
|----------------------|-----------------------------------------------------------------------|
|type:                 |ボタンの種類です。                                                     |
|x:                    |ボタンのX座標です。                                                    |
|y:                    |ボタンのY座標です。                                                    |
|width:                |ボタンの幅です。                                                       |
|height:               |ボタンの高さです。                                                     |
|label:                |ラベルの指定です。                                                     |
|index:                |セーブ・ロード・ヒストリのボタンでページ内のスロット番号です。         |
|clear-r:              |ボタンの背景クリア色です。白っぽいボタンなら白のRGBコードを指定します。|
|clear-g:              |ボタンの背景クリア色です。白っぽいボタンなら白のRGBコードを指定します。|
|clear-b:              |ボタンの背景クリア色です。白っぽいボタンなら白のRGBコードを指定します。|
|margin:               |セーブ・ロード・ヒストリのボタンで、内側のマージンです。               |
|pointse:              |ボタンがポイントされたときに再生するSEです。                           |
|clickse:              |ボタンがクリックされたときに再生するSEです。                           |

## スライダーボタンについて

アクティブ画像にスライダーのノブを描いておきます。
サンプルゲームを参考にしてください。

横長のスライダーの場合、ノブの幅と高さはボタンの高さと等しくなります。
縦長のスライダーの場合、ノブの幅と高さはボタンの幅と等しくなります。

## ヒストリーやセーブ画面での調整

セーブ・ロード・ヒストリのスロット内の文字に、灰色のふちどりが生じることがあります。
これは、透明なピクセルのRGB値が黒になっているからです。
ふちどりを消すには、ボタンの定義に以下のように背景色を記述します。

```
# 背景色
clear-r: 255;
clear-g: 255;
clear-b: 255;
```

ファイル記載例は下記の通りです。

```
# セーブデータ1番目
SAVESLOT1 {
   # 種類:セーブ
   type: save;

   # セーブデータ番号0
   index: 0;

   # 背景色
   clear-r: 255;
   clear-g: 255;
   clear-b: 255;

   # 座標とサイズ
   x: 167;
   y: 153;
   width: 950;
   height: 162;

   # 画像とテキストのマージン
   margin: 20;

   # ポイントされたときの効果音
   pointse: btn-change.ogg;

   # クリックされたときの効果音
   clickse: click.ogg;

}
```

## 独自メニュー画面について

システムボタンが押されたときに表示されるメニューに、独自のメニューボタンをいくつでも追加できます。
たとえば、ゲームの進行に合わせて内容が変化するメニューを作ることもできます。
このようなメニュー画面を作る際に必要となる機能を紹介します。

### メニュー画面から別なメニュー画面へジャンプする場合

```
# 独自メニュー画面にジャンプするボタン
MY_MENU_1 {
   type: gui;
   file: my-menu-1.txt;
}
```

### メニュー画面からシナリオファイル内のラベルへジャンプして戻らない場合

```
# ラベルにジャンプするボタン
MY_MENU_1 {
   type: goto;
   label: my-menu-1-label;
}
```

### メニュー画面からシナリオファイル内のラベルへジャンプして戻る場合

カスタムメニューを作ってその中でシナリオファイルを呼び出す構成を採ることが可能です。

```
button {
   type: goto;
   label: my-menu-1-label;
   gosub: yes;
}
```

上記のボタンが押されると、シナリオのラベル `my-menu-1-label` にジャンプが行われます。
シナリオで `@return` を使用すると、元の位置に戻ります。
また、`gosub: yes;` の代わりに `gosub-gui: yes;` を使えば、`@return` で元の GUI に戻るように変更できます。

もしも、呼び出し先から背景やキャラを変更して、それを元に戻したい場合には、`pushstage` 指定と WMS の `s2_pop_stage()` を組み合わせ、下記のようにします。

```
button {
   type: goto;
   label: my-menu-1-label;
   gosub: yes;
   pushstage: yes;
}
```

`@return` の前に、WMSの `s2_pop_stage()` を利用することで、背景やキャラを復元できます。
