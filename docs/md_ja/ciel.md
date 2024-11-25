Cielシステムとは
================

Cielシステムは、YU-RIS/ERISに影響を受けたコマンド群です。

機能性が根本的に異なることから、
[@bg](reference.html#bg) /
[@ch](reference.html#ch) /
[@move](reference.html#move) /
[@chch](reference.html#chch)
との併用はできません。

## 使用例

```
# 背景を指定します。（この時点では表示されません。）
@cl.file name=bg file=roof.png

# ステージにキャラクタを入場させます。（@chと違って位置指定は存在せず、この時点では表示もされません。）
@cl.enter name=hina

# 入場済みのキャラクタに画像のロード、座標指定、アルファ値の指定を行います。
@cl.file name=hina file=001-normal.png
@cl.pos name=hina align=center x+=100
@cl.alpha name=hina a=255

# フェードの種類を指定します。
@cl.effect effect=normal

# フェードの時間を指定します。
@cl.time t=0.5

# 画面にフェードで反映します。
@cl.run
```

## コマンド一覧

|コマンド                            |役割                                                                                                    |
|------------------------------------|--------------------------------------------------------------------------------------------------------|
|@cl.enter name=名前                 |ステージにキャラを入場させる。入場は1回でよい。退場させるまで名前が有効。                               |
|@cl.leave name=名前                 |ステージからキャラを退場させる。name=allで全員退場。                                                    |
|@cl.file name=名前 file=chara001.png|指定した名前のキャラのファイルを指定する(拡張子は省略可)。name=bgで背景も指定可能。                     |
|@cl.pos name=名前 align=left x+=100 |キャラの位置を指定する。(align=,valign=,x=,x+=,x-=,y=,y+=,y-=の形式で指定可能)                          |
|@cl.alpha name=名前 a=255           |キャラのアルファ値を指定する。                                                                          |
|@cl.dim name=名前 dim=true          |キャラを暗くするかの手動設定を行う。dim=trueかdim=false                                                 |
|@cl.time t=0.5                      |フェードやアニメの時間を指定する。                                                                      |
|@cl.effect effect=normal            |フェードのエフェクトを指定する。                                                                        |
|@cl.move name=名前 t=0.5 x+=100     |アニメの指定を追加する。振動のような周期的なアニメを簡単に記述できる。x=,x+=,x-=,y=,y+=,y-=,a=が使える。|
|@cl.run                             |フェードかアニメを実行する。(moveが使われていればアニメとなる。そうでなければフェードとなる。)          |
|@cl.async                           |アニメを実行しながら次のコマンドに移動する。                                                            |

## アニメの例

キャラクタ `hina` を頷かせます。

```
@cl.move name=hina t=0.3 y-=100
@cl.move name=hina t=0.3 y+=100
@cl.move name=hina t=0.3 y-=100
@cl.move name=hina t=0.3 y+=100
@cl.run
```

最後の `@cl.run` を `@cl.async` に置き換えると、アニメの完了を待つことなく、次のメッセージに進みます。

## マクロとの組み合わせ

Ciel は一つの演出に複数行の記述が必要で、煩雑な記述になるため、[@gosub](reference.html#gosub) マクロとの組み合わせが想定されています。

```
&hina happy
```

呼び出し先のマクロは下記のように定義します。
引数は `&1` のように番号で書くと展開されます。

```
:hina
@cl.file name=hina file=hina-&1.png
@cl.run
@return
```
