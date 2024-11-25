WMS
===

WMS は OpenNovel プロジェクトによって開発された汎用のプログラミング言語です。
WMS はシナリオファイルの好きなところから [@wms](reference.html#wms) コマンドで呼び出すことができます。

## 何に使うの？

設定ファイルの一括書き換えや、複雑な分岐条件の記述に使います。

OpenNovel のシナリオのスクリプトは、ストーリーの自然な流れにフォーカスしており、複雑な条件で分岐を表現するのが苦手です。
そこで用意されたのが WMS で、複雑なプログラムをとても簡単に記述できます。
少しでもプログラミング経験があればすぐに使えるように、非常に簡単な言語仕様にしてあります。

## 基本の使い方

例えば文字の色は `project.txt` の中で次のようにコンフィグで指定されていますよね。

```
msgbox.font.r=255
msgbox.font.g=255
msgbox.font.b=255
```

シナリオファイルでこれを変更する場合、下記のようになります。

```
@config msgbox.font.r 255
@config msgbox.font.g 255
@config msgbox.font.b 255
```

プラグインスクリプトを使うと、これをシナリオファイルで1行で変更することができます。
ます、次のスクリプトを `wms/change-color.txt` として保存します。

```
func main() {
    s2_set_config("msgbox.font.r", "128");
    s2_set_config("msgbox.font.g", "128");
    s2_set_config("msgbox.font.b", "128");
}
```

`init.txt` の中で次のように呼び出してみてください。

```
今から文字の色が変わります。
@wms change-color.txt
文字の色が変わりました。
```

使い方の基本はこれだけです。

## 文法

WMS を用いると汎用的なプログラミングが行えます。
ここでは文法について説明します。

### プログラムは main() 関数から始まる

```
func main() {
    // これはコメントです
    print("Hello, world!");
}
```

### 関数は他の関数を呼び出しできる

```
func main() {
    foo(0, 1, 2);
}

func foo(a, b, c) {
    return a + b + c;
}
```

### 文字列変数による間接呼び出しが可能

```
func main() {
    myfunc = "foo";
    myfunc(0, 1, 2);
}

func foo(a, b, c) {
    return a + b + c;
}

func myfunc(a, b, c) {
    // この関数は呼び出されません。foo()が呼び出されます。
}
```

### 型と変数

プログラム中では整数、浮動小数点数、文字列、配列の変数と値を利用できます。

```
func main() {
    // 整数
    a = 1;
    if(isint(a)) {
        print("a is int");
    }

    // 浮動小数点数
    b = 1.0;
    if(isfloat(b)) {
        print("b is float");
    }

    // 文字列
    c = "string";
    if(isstr(c)) {
        print("c is string");
    }

    // 配列 (整数インデックス)
    d[0] = 0;
    if(isarray(d)) {
        print("d is array");
    }

    // 配列 (文字列インデックス)
    e["abc"] = 0;
    if(isarray(e)) {
        print("e is array");
    }

    // 配列の配列
    f["key"] = e;
    if(isarray(f)) {
        print("f is array");
        if(isarray(f[0])) {
            print("f[0] is array");
        }
    }
}
```

### 計算

整数と浮動小数点数は加算、減算、乗算、除算が可能です。

整数は下記のようになります。

```
a = 1;
b = 2;
c = a + b;
// a += b; の形式はサポートされていません。
```

また、浮動小数点は下記のようになります。

```
a = 1.0;
b = 2.0;
c = a + b;
```

整数と浮動小数点数を組み合わせると、結果は浮動小数点数になります。

```
a = 1;
b = 2.0;
c = a + b; // cは浮動小数点数
```

整数は除算の余り（剰余）を求めることができます。

```
a = 3;
b = a % 2; // 結果は3÷2の余りである1
```

文字列は+で連結可能です。

```
a = "aaa";
b = "bbb";
c = a + b;
```

文字列＋整数は文字列ですが、整数＋文字列は整数です。

### 回数ループ

指定した回数の繰り返し:

```
func main() {
    for(i in 0..9) {
        print(i);
    }
}
```

### 配列の値についての繰り返し:

```
func main() {
    a[0] = 0;
    a[1] = 1;
    a[2] = 2;
    for(value in a) {
        print(value);
    }
}
```

### 配列のキー/値ペアについての繰り返し:
```
func main() {
    a["key1"] = 0;
    a["key2"] = 1;
    a["key3"] = 2;

    for(key, value in a) {
        print(key + "=" + value);
    }
}
```

## 単純な while ループ:

```
func main() {
    a = 10;
    while (a &gt; 0) {
        print(a);
        a = a - 1;
    }
}
```

### break と continue:

```
func main() {
    for(i in 0..9) {
        if(i == 2) {
            continue;
        }
        if(i == 7) {
            break;
        }
    }
}
```

### 分岐

プログラムは if - else if - else で分岐できます。

```
func main() {
    a = foo();
    if(a &gt; 10) {
        print("a &gt; 10");
    } else if(a &gt; 5) {
        print("a &gt; 5");
    } else {
        print("else");
    }
}

func foo() {
    return 6;
}
```

### 配列

配列の要素はキー(インデックス)を持ち、キーには整数、浮動小数点数、文字列が使えます。
1つの配列の中で、整数、浮動小数点数、文字列のキーを混在させられます。

配列を作成するには、値を [key] の文法で代入します。

```
func main() {
    a[0] = 0;
    print(a);
}
```

配列の要素を削除するには、remove() を使います。

```
func main() {
    a[0] = 0;
    remove(a, 0);
    print(a);
}
```

配列の要素数を取得するには、size() を使います。

```
func main() {
    a[0] = 0;
    print(size(a));
}
```

### 型変換

整数から文字列:

```
s = "" + 123;
```

浮動小数点数から文字列:

```
s = "" + 1.23;
```

整数から浮動小数点数:

```
f = 0.0 + 123;
```

文字列から整数:

```
i = 0 + "123";
```

文字列から浮動小数点数:

```
f = 0.0 + "1.23";
```

文法については以上です。

## エンジンからWMSの呼び出し

[@wms](reference.html#wms) コマンドで呼び出しできます。
引数を指定すると `main()` 関数の引数として渡されます。
`main()` 関数の引数は最大10個までです。

## WMSからエンジンの呼び出し

WMS のスクリプトからエンジンを操作するための関数が提供されてます。
これらの関数は名前に `s2_` という接頭辞を持ちます。

### フラグ用変数の値を取得する

`s2_get_variable()` はフラグ用変数のインデックスを受け取り、フラグ用変数の値を返します。

```
value = s2_get_variable(100);
```

### フラグ用変数の値を設定する

`s2_set_variable()` はフラグ用変数のインデックスと値を受け取って、フラグ用変数の値を変更します。

```
s2_set_variable(100, 1);
```

### ランダムな数(乱数)を取得する

`s2_random()` はランダムな整数を返します。戻り値の範囲は `0` から `9999` です。

```
value = s2_random();
```

### コンフィグを書き換える

`s2_set_config()` はコンフィグ名の文字列と、コンフィグ値の文字列を受け取り、コンフィグを書き換えます。

```
s2_set_config("msgbox.x", "0");
s2_set_config("msgbox.y", "0");
```

## 使用例

コピペで使える事例集です。

### 変数を取得し、計算した後、ゲーム内変数に書き込む

```
func main() {
    // 変数を取得する
    a = s2_get_variable(0);
    b = s2_get_variable(1);
    c = s2_get_variable(2);

    // 合計を計算する
    sum = a + b + c;

    // 変数100番に書き込む
    s2_set_variable(100, sum);
}
```

### ゲーム内で現実の日時を取得

`get-datetime.txt` に以下のように記述します。

```
func main() {
    // 日時を取得
    now_y  = s2_get_year();
    now_mo = s2_get_month();
    now_d  = s2_get_day();
    now_h  = s2_get_hour();
    now_mi = s2_get_minute();
    now_s  = s2_get_second();
    now_w  = s2_get_wday();    // 0=日、 1=月、 2=火……

    // ゲーム内の変数$1に曜日を代入
    s2_set_variable(1, now_w);
}
```

シナリオファイルで以下のようにすると、現実の曜日によってメッセージを変えられます。

```
@wms get-datetime.txt

<<<
if $1 == 0 {
    今日は日曜日です。
}
if $1 == 1 {
    今日は月曜日です。
}
if $1 == 2 {
    今日は火曜日です。
}
if $1 == 3 {
    今日は水曜日です。
}
if $1 == 4 {
    今日は木曜日です。
}
if $1 == 5 {
    今日は金曜日です。
}
if $1 == 6 {
    今日は土曜日です。
}
>>>
```
