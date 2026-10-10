#!/usr/bin/env python3
"""
Gera o index.html do repositório de estudos.

Uso (na raiz do repositório):
    python gerar_index.py                  # lê a pasta onde o script está e grava index.html nela
    python gerar_index.py CAMINHO_DA_RAIZ  # lê outra pasta

O index.html resultante é um arquivo único: guias (.md), demonstrações (.html),
códigos (.c) e imagens ficam embutidos nele. Sempre que você mexer nos arquivos
do repositório, rode o script de novo para atualizar o índice.
"""
import base64
import json
import re
import sys
from pathlib import Path

# ---------------------------------------------------------------------------
# Configuração (edite à vontade)
# ---------------------------------------------------------------------------
TITULO = "Estudos de AEDS 2"
DESCRICAO = "Guias, demonstrações interativas e códigos em C de algoritmos e estruturas de dados."

IGNORAR_PASTAS = {"node_modules", "__pycache__", "venv", "dist", "build"}  # pastas que começam com "." já são ignoradas
IGNORAR_ARQUIVOS = {"index.html", "gerar_index.py"}

# Ordem preferida das pastas (minúsculas). O que não estiver aqui vem depois, em ordem alfabética.
ORDEM_PASTAS = [
    "ordenacoes", "lista", "fila", "pilha", "celulaestrutura", "estudos",
    "insercao", "selecao", "counting", "radix", "bucket", "merge", "quick", "heap",
]

# Nome exibido para pastas (chave em minúsculas)
NOMES_PASTAS = {
    "ordenacoes": "Ordenações",
    "insercao": "Insertion Sort",
    "selecao": "Selection Sort",
    "counting": "Counting Sort",
    "radix": "Radix Sort",
    "bucket": "Bucket Sort",
    "merge": "Merge Sort",
    "quick": "Quick Sort",
    "heap": "Heap Sort",
    "lista": "Listas",
    "fila": "Filas",
    "pilha": "Pilhas",
    "pilhaencadeadanormal": "Pilha encadeada normal",
    "celulaestrutura": "Células",
    "estudos": "Estudos",
    "listaflexivel": "Lista flexível",
    "listasimples": "Lista simples",
    "listaduplaencadeada": "Lista dupla encadeada",
    "listaencadeada": "Lista encadeada",
    "filaduplamenteencadeada": "Fila duplamente encadeada",
    "filacircular": "Fila circular",
    "filaencadeadanormal": "Fila encadeada normal",
    "filacircularestudos": "Fila circular (estudos)",
}

# Nome exibido para arquivos (chave = nome do arquivo em minúsculas)
NOMES_ARQUIVOS = {
    "insercao.c": "Insertion Sort",
    "selecao.c": "Selection Sort",
    "countingsort.c": "Counting Sort",
    "radixsort.c": "Radix Sort",
    "bucketsort.c": "Bucket Sort",
    "mergesort.c": "Merge Sort",
    "quicksort.c": "Quick Sort",
    "heapsort.c": "Heap Sort",
    "image.png": "Imagem",
    "filacircular.md": "Fila circular: conceitos",
    "pilhainserir.c": "Pilha: inserir (empilhar)",
    "pilharemover.c": "Pilha: remover (desempilhar)",
    "celula.c": "Célula",
    "celuladupla.c": "Célula dupla",
    "celulacabeca.c": "Célula com cabeça",
    "testefilacircular.c": "Teste da fila circular",
}

# Correções para nomes de arquivo que perderam acentos ao serem salvos
CORRECOES = [("espa o", "espaço"), ("seguran a", "segurança"), ("Demonstra o", "Demonstração")]

TIPOS = {
    ".md": "guia", ".markdown": "guia",
    ".html": "demo", ".htm": "demo",
    ".c": "codigo", ".h": "codigo", ".cpp": "codigo", ".py": "codigo", ".java": "codigo", ".js": "codigo",
    ".png": "img", ".jpg": "img", ".jpeg": "img", ".gif": "img", ".webp": "img", ".svg": "img",
}
MIME_IMG = {".png": "image/png", ".jpg": "image/jpeg", ".jpeg": "image/jpeg",
            ".gif": "image/gif", ".webp": "image/webp", ".svg": "image/svg+xml"}


# ---------------------------------------------------------------------------
# Nomes legíveis
# ---------------------------------------------------------------------------
def _titulo(texto: str) -> str:
    return " ".join(p[:1].upper() + p[1:] for p in texto.split())


def _limpar(base: str) -> str:
    base = re.sub(r"\s*\(\d+\)$", "", base)                                   # "nome (1)" -> "nome"
    base = re.sub(r"[_\-]+", " ", base)
    base = re.sub(r"(?<![A-Z])([A-Z])([A-Z])(?=[a-z])", lambda m: m[1] + m[2].lower(), base)  # LIsta -> Lista
    base = re.sub(r"(?<=[a-z])(?=[A-Z])", " ", base)                          # camelCase -> camel Case
    base = re.sub(r"(?<=[A-Za-z])(?=\d)", " ", base)                          # lista2 -> lista 2
    return re.sub(r"\s+", " ", base).strip()


def nome_pasta(nome: str) -> str:
    return NOMES_PASTAS.get(nome.lower()) or _titulo(_limpar(nome))


def nome_arquivo(nome: str, na_raiz: bool) -> str:
    if not na_raiz and nome.lower() in NOMES_ARQUIVOS:
        return NOMES_ARQUIVOS[nome.lower()]
    base = _limpar(Path(nome).stem)
    baixo = base.lower()
    if baixo.startswith("guia completo "):
        return "Guia completo: " + _titulo(baixo[len("guia completo "):])
    if baixo.startswith("demonstra o do "):
        return "Demonstração: " + _titulo(baixo[len("demonstra o do "):])
    if baixo.startswith("demo "):
        return "Demonstração: " + _titulo(baixo[len("demo "):])
    if baixo.startswith("visualizador interativo do "):
        return "Visualizador: " + _titulo(baixo[len("visualizador interativo do "):])
    for errado, certo in CORRECOES:
        base = base.replace(errado, certo)
    return base[:1].upper() + base[1:]


# ---------------------------------------------------------------------------
# Leitura do repositório
# ---------------------------------------------------------------------------
def natural(texto: str):
    return [int(p) if p.isdigit() else p for p in re.split(r"(\d+)", texto.lower())]


def chave(caminho: Path):
    if caminho.is_dir():
        nome = caminho.name.lower()
        pos = ORDEM_PASTAS.index(nome) if nome in ORDEM_PASTAS else 999
        return (0, pos, natural(caminho.name), "")
    return (1, 0, natural(caminho.stem), caminho.name.lower())


def ler_texto(caminho: Path) -> str:
    dados = caminho.read_bytes()
    for codificacao in ("utf-8-sig", "cp1252", "latin-1"):
        try:
            return dados.decode(codificacao)
        except UnicodeDecodeError:
            continue
    return dados.decode("utf-8", errors="replace")


def construir(caminho: Path, raiz: Path):
    rel = caminho.relative_to(raiz).as_posix()
    rel = "" if rel == "." else rel
    if caminho.is_dir():
        filhos = []
        for c in sorted(caminho.iterdir(), key=chave):
            if c.name.startswith(".") or c.name in IGNORAR_PASTAS:
                continue
            if c.is_file() and c.name in IGNORAR_ARQUIVOS and c.parent == raiz:
                continue
            no = construir(c, raiz)
            if no is not None:
                filhos.append(no)
        if not filhos and rel:
            return None  # pasta vazia não aparece
        return {"tipo": "dir", "nome": TITULO if not rel else nome_pasta(caminho.name),
                "arq": caminho.name, "path": rel, "children": filhos}

    ext = caminho.suffix.lower()
    kind = TIPOS.get(ext, "outro")
    no = {"tipo": "file", "nome": nome_arquivo(caminho.name, caminho.parent == raiz),
          "arq": caminho.name, "path": rel, "ext": ext.lstrip("."), "kind": kind,
          "tamanho": caminho.stat().st_size}
    if kind == "img":
        no["uri"] = f"data:{MIME_IMG.get(ext, 'application/octet-stream')};base64," + \
                    base64.b64encode(caminho.read_bytes()).decode("ascii")
    else:
        no["conteudo"] = ler_texto(caminho)
    return no


# ---------------------------------------------------------------------------
# Template do index.html
# ---------------------------------------------------------------------------
TEMPLATE = r'''<!DOCTYPE html>
<html lang="pt-BR">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>__TITULO__</title>
<link rel="preconnect" href="https://fonts.googleapis.com">
<link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
<link href="https://fonts.googleapis.com/css2?family=JetBrains+Mono:wght@400;600&family=Manrope:wght@400;600;700;800&display=swap" rel="stylesheet">
<link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/KaTeX/0.16.9/katex.min.css">
<script>
/* aplica o tema salvo antes de desenhar a página, para não piscar */
try{var t=localStorage.getItem('tema');if(t)document.documentElement.dataset.theme=t}catch(e){}
</script>
<style>
/* ==========================================================================
   1. TOKENS (cores, tipografia, medidas)
   ========================================================================== */
:root{
  color-scheme:light;
  --bg:#eef2f5; --panel:#ffffff; --panel-2:#f6f9fb;
  --ink:#14232e; --ink-2:#3b4f5c; --mute:#667c89;
  --line:#d3dee5; --line-2:#e6edf1;
  --acc:#0f7c8a; --acc-ink:#ffffff; --acc-soft:#dcf0f2;
  --k-guia:#0f7c8a; --k-demo:#b97d00; --k-codigo:#6552d0; --k-img:#2e8b57; --k-outro:#667c89;
  --code-bg:#f5f8fa;
  --tk-kw:#6552d0; --tk-ty:#0f7c8a; --tk-str:#b2551d; --tk-num:#a4437b; --tk-com:#7b8e99; --tk-fn:#1f6fb5; --tk-meta:#8a6d00;
  --r:12px; --side:310px; --top:58px;
  --ui:"Manrope",system-ui,-apple-system,"Segoe UI",sans-serif;
  --mono:"JetBrains Mono",ui-monospace,SFMono-Regular,Menlo,Consolas,monospace;
}
@media (prefers-color-scheme:dark){
  :root:not([data-theme="light"]){
    color-scheme:dark;
    --bg:#0e171d; --panel:#152229; --panel-2:#1a2a32;
    --ink:#e5eef2; --ink-2:#b7c8d1; --mute:#8aa0ac;
    --line:#28404b; --line-2:#203540;
    --acc:#45c1d0; --acc-ink:#05242a; --acc-soft:#173a42;
    --k-guia:#45c1d0; --k-demo:#f0b429; --k-codigo:#9d8cff; --k-img:#5cc08a; --k-outro:#8aa0ac;
    --code-bg:#101c22;
    --tk-kw:#b4a7ff; --tk-ty:#5fd0de; --tk-str:#f0a070; --tk-num:#f08fc0; --tk-com:#7d94a0; --tk-fn:#7cb8f0; --tk-meta:#e6c35c;
  }
}
:root[data-theme="dark"]{
  color-scheme:dark;
  --bg:#0e171d; --panel:#152229; --panel-2:#1a2a32;
  --ink:#e5eef2; --ink-2:#b7c8d1; --mute:#8aa0ac;
  --line:#28404b; --line-2:#203540;
  --acc:#45c1d0; --acc-ink:#05242a; --acc-soft:#173a42;
  --k-guia:#45c1d0; --k-demo:#f0b429; --k-codigo:#9d8cff; --k-img:#5cc08a; --k-outro:#8aa0ac;
  --code-bg:#101c22;
  --tk-kw:#b4a7ff; --tk-ty:#5fd0de; --tk-str:#f0a070; --tk-num:#f08fc0; --tk-com:#7d94a0; --tk-fn:#7cb8f0; --tk-meta:#e6c35c;
}

/* ==========================================================================
   2. BASE
   ========================================================================== */
*,*::before,*::after{box-sizing:border-box}
html{scroll-padding-top:calc(var(--top) + 12px)}
body{margin:0;background:var(--bg);color:var(--ink);font:15.5px/1.6 var(--ui);-webkit-font-smoothing:antialiased}
a{color:inherit;text-decoration:none}
button,input{font:inherit;color:inherit}
:focus-visible{outline:3px solid var(--acc);outline-offset:2px;border-radius:6px}
.ic{width:1.15em;height:1.15em;fill:none;stroke:currentColor;stroke-width:1.7;stroke-linecap:round;stroke-linejoin:round;flex:none}

/* ==========================================================================
   3. BARRA SUPERIOR
   ========================================================================== */
.top{position:sticky;top:0;z-index:30;height:var(--top);display:flex;align-items:center;gap:12px;padding:0 16px;background:var(--panel);border-bottom:1px solid var(--line)}
.brand{display:flex;align-items:center;gap:10px;font-weight:800;letter-spacing:-.01em}
.mark{width:30px;height:30px;border-radius:8px;background:var(--acc);color:var(--acc-ink);display:grid;place-items:center;font:600 13px var(--mono)}
.grow{flex:1}
.btn{display:inline-flex;align-items:center;gap:6px;height:34px;padding:0 12px;border:1px solid var(--line);border-radius:9px;background:var(--panel);cursor:pointer;font-weight:600;font-size:.85rem}
.btn:hover{border-color:var(--acc)}
.btn.icon{width:36px;height:36px;padding:0;justify-content:center}
.menu{display:none}
.search{position:relative;width:min(340px,40vw)}
.search input{width:100%;height:36px;padding:0 12px 0 34px;border:1px solid var(--line);border-radius:9px;background:var(--panel-2)}
.search .ic{position:absolute;left:10px;top:50%;transform:translateY(-50%);color:var(--mute)}

/* ==========================================================================
   4. ESTRUTURA (barra lateral + conteúdo)
   ========================================================================== */
.shell{display:grid;grid-template-columns:var(--side) minmax(0,1fr);align-items:start}
.side{position:sticky;top:var(--top);height:calc(100dvh - var(--top));overflow:auto;padding:14px 10px 28px;border-right:1px solid var(--line);background:var(--panel)}
main{padding:22px clamp(16px,3vw,40px) 60px;min-width:0}
.scrim{display:none}

/* ==========================================================================
   5. ÁRVORE DE PASTAS
   ========================================================================== */
.tree,.tree ul{list-style:none;margin:0;padding:0}
.tree ul{margin-left:14px;padding-left:8px;border-left:1px solid var(--line-2);display:none}
.tree li.open>ul{display:block}
.row{display:flex;align-items:center;gap:6px;min-height:32px;border-radius:8px}
.row:hover{background:var(--panel-2)}
.row.on{background:var(--acc-soft);color:var(--ink)}
.tog{width:24px;height:24px;border:0;background:none;display:grid;place-items:center;cursor:pointer;color:var(--mute);border-radius:6px}
.tog .ic{transition:transform .15s}
li.open>.row .tog .ic{transform:rotate(90deg)}
.name,.file,.home{display:flex;align-items:center;gap:8px;min-width:0;font-weight:600;font-size:.92rem}
.name{flex:1;padding:4px 8px 4px 2px}
.home{padding:4px 8px;font-weight:700}
.file{padding:4px 8px 4px 30px;font-weight:500;font-size:.88rem;color:var(--ink-2)}
.name span,.file span,.home span{overflow:hidden;text-overflow:ellipsis;white-space:nowrap}
.name .ic{color:var(--acc)}
.file .ic{color:var(--k-outro)}
.file.k-guia .ic{color:var(--k-guia)}
.file.k-demo .ic{color:var(--k-demo)}
.file.k-codigo .ic{color:var(--k-codigo)}
.file.k-img .ic{color:var(--k-img)}
.none{padding:10px;color:var(--mute);font-size:.9rem}

/* ==========================================================================
   6. CABEÇALHO DA PÁGINA E MIGALHAS
   ========================================================================== */
.crumbs{display:flex;flex-wrap:wrap;align-items:center;gap:6px;margin-bottom:10px;color:var(--mute);font-size:.85rem}
.crumbs a:hover{color:var(--acc);text-decoration:underline}
.crumbs [aria-current]{color:var(--ink-2);font-weight:600}
.sep{opacity:.5}
.head h1{margin:0 0 6px;font-size:clamp(1.6rem,3.2vw,2.3rem);line-height:1.15;letter-spacing:-.02em;font-weight:800}
.head .sub{margin:0 0 8px;max-width:62ch;color:var(--ink-2)}
.tally{margin:0;color:var(--mute);font-size:.9rem}
h2.sec{margin:28px 0 12px;font-size:1.05rem;font-weight:700}

/* ==========================================================================
   7. CARDS DE PASTAS
   ========================================================================== */
.cards{display:grid;grid-template-columns:repeat(auto-fill,minmax(250px,1fr));gap:12px}
.card{display:flex;flex-direction:column;gap:6px;padding:14px 16px;background:var(--panel);border:1px solid var(--line);border-radius:var(--r);transition:border-color .15s,transform .15s}
.card:hover{border-color:var(--acc);transform:translateY(-2px)}
.card-top{display:flex;align-items:center;gap:8px;font-size:1.02rem}
.card-top .ic{color:var(--acc)}
.path{font:.76rem var(--mono);color:var(--mute)}
.pills{display:flex;flex-wrap:wrap;gap:6px;margin-top:4px}
.pill{display:inline-flex;align-items:center;gap:6px;padding:2px 9px;border:1px solid var(--line-2);border-radius:99px;background:var(--panel-2);color:var(--ink-2);font-size:.78rem;font-weight:600}
.pill i{width:8px;height:8px;border-radius:50%;background:var(--k-outro)}
.pill.k-guia i{background:var(--k-guia)}
.pill.k-demo i{background:var(--k-demo)}
.pill.k-codigo i{background:var(--k-codigo)}
.pill.k-img i{background:var(--k-img)}

/* ==========================================================================
   8. ABAS, CHIPS E VISUALIZADOR
   ========================================================================== */
.tabs{display:flex;flex-wrap:wrap;gap:4px;margin-top:24px;border-bottom:1px solid var(--line)}
.tab{display:inline-flex;align-items:center;gap:8px;margin-bottom:-1px;padding:9px 14px;border:1px solid transparent;border-bottom:0;border-radius:10px 10px 0 0;color:var(--ink-2);font-weight:700;font-size:.92rem}
.tab:hover{color:var(--ink)}
.tab[aria-selected="true"]{background:var(--panel);border-color:var(--line);color:var(--ink)}
.tab .ic{color:var(--k-outro)}
.tab.k-guia .ic{color:var(--k-guia)}
.tab.k-demo .ic{color:var(--k-demo)}
.tab.k-codigo .ic{color:var(--k-codigo)}
.tab.k-img .ic{color:var(--k-img)}
.tab small{color:var(--mute);font-weight:600}
.viewer{background:var(--panel);border:1px solid var(--line);border-top:0;border-radius:0 0 var(--r) var(--r);overflow:hidden}
.chips{display:flex;flex-wrap:wrap;gap:6px;padding:12px 14px;border-bottom:1px solid var(--line-2)}
.chip{padding:4px 12px;border:1px solid var(--line);border-radius:99px;background:var(--panel);color:var(--ink-2);font-size:.85rem;font-weight:600}
.chip:hover{border-color:var(--acc)}
.chip[aria-current="true"]{background:var(--acc);border-color:var(--acc);color:var(--acc-ink)}
.vbar{display:flex;align-items:center;gap:12px;padding:10px 14px;border-bottom:1px solid var(--line-2);font-size:.82rem}
.vpath{min-width:0;overflow:hidden;text-overflow:ellipsis;white-space:nowrap;font-family:var(--mono);color:var(--ink-2)}
.vinfo{white-space:nowrap;color:var(--mute)}
.vact{display:flex;gap:8px;margin-left:auto}
.vbody{min-height:200px}
.empty{padding:28px;color:var(--mute)}

/* ---- código ---- */
.code{display:grid;grid-template-columns:auto minmax(0,1fr);max-height:calc(100dvh - 300px);min-height:200px;overflow:auto;background:var(--code-bg)}
.code pre{margin:0;font:13.5px/1.65 var(--mono)}
.ln{position:sticky;left:0;padding:14px 12px 14px 16px;border-right:1px solid var(--line-2);background:var(--code-bg);color:var(--mute);text-align:right;user-select:none}
.src{padding:14px 18px;tab-size:4}
.src code{padding:0;background:none;font:inherit}
.hljs-keyword,.hljs-literal{color:var(--tk-kw);font-weight:600}
.hljs-type,.hljs-built_in{color:var(--tk-ty)}
.hljs-string{color:var(--tk-str)}
.hljs-number{color:var(--tk-num)}
.hljs-comment{color:var(--tk-com);font-style:italic}
.hljs-title,.hljs-function .hljs-title{color:var(--tk-fn)}
.hljs-meta,.hljs-meta .hljs-keyword{color:var(--tk-meta)}
.hljs-meta .hljs-string{color:var(--tk-str)}

/* ---- guia (markdown) ---- */
.prose{max-width:900px;padding:8px clamp(18px,3vw,40px) 32px;overflow-wrap:break-word}
.prose h1{margin:1.2em 0 .5em;font-size:1.9rem;line-height:1.2;letter-spacing:-.02em}
.prose h2{margin:2em 0 .6em;padding-top:.5em;border-top:1px solid var(--line-2);font-size:1.35rem}
.prose h3{margin:1.6em 0 .4em;font-size:1.1rem}
.prose p,.prose li{max-width:75ch}
.prose ul,.prose ol{padding-left:1.4em}
.prose li{margin:.25em 0}
.prose blockquote{margin:1em 0;padding:.6em 1em;border-left:4px solid var(--acc);border-radius:0 8px 8px 0;background:var(--acc-soft)}
.prose blockquote p{margin:.3em 0}
.prose hr{margin:2em 0;border:0;border-top:1px solid var(--line)}
.prose code{padding:.1em .38em;border:1px solid var(--line-2);border-radius:5px;background:var(--code-bg);font:.88em var(--mono)}
.prose pre{padding:14px 16px;overflow:auto;border:1px solid var(--line-2);border-radius:10px;background:var(--code-bg);font:13.5px/1.6 var(--mono)}
.prose pre code{padding:0;border:0;background:none;font:inherit}
.table-wrap{margin:1em 0;overflow:auto;border:1px solid var(--line);border-radius:10px}
.prose table{width:100%;border-collapse:collapse;font-size:.92rem}
.prose th,.prose td{padding:8px 12px;border-bottom:1px solid var(--line-2);text-align:left;vertical-align:top}
.prose th{background:var(--panel-2);font-weight:700;white-space:nowrap}
.prose tr:last-child td{border-bottom:0}

/* ---- demonstração e imagem ---- */
.frame{display:block;width:100%;height:calc(100dvh - 250px);min-height:560px;border:0;background:#fff}
.imgwrap{padding:18px;text-align:center}
.imgwrap img{max-width:100%;height:auto;border:1px solid var(--line-2);border-radius:8px}

/* ==========================================================================
   9. RESPONSIVO
   ========================================================================== */
@media (max-width:900px){
  .menu{display:inline-flex}
  .brand span{display:none}
  .search{width:auto;flex:1}
  .shell{grid-template-columns:1fr}
  .side{position:fixed;top:var(--top);bottom:0;left:0;z-index:40;width:min(86vw,340px);height:auto;transform:translateX(-102%);transition:transform .2s;box-shadow:0 12px 40px rgba(0,0,0,.25)}
  body.nav-open .side{transform:none}
  body.nav-open .scrim{display:block;position:fixed;inset:var(--top) 0 0 0;z-index:35;background:rgba(0,0,0,.4)}
  .code{max-height:none}
  .frame{height:75dvh;min-height:420px}
}
@media (prefers-reduced-motion:reduce){*{transition:none!important}}
</style>
</head>
<body>
<svg width="0" height="0" style="position:absolute" aria-hidden="true"><defs>
  <symbol id="i-dir" viewBox="0 0 24 24"><path d="M3 6.5A1.5 1.5 0 0 1 4.5 5H9l2 2.5h8.5A1.5 1.5 0 0 1 21 9v8.5a1.5 1.5 0 0 1-1.5 1.5h-15A1.5 1.5 0 0 1 3 17.5z"/></symbol>
  <symbol id="i-guia" viewBox="0 0 24 24"><path d="M5 4.5A1.5 1.5 0 0 1 6.5 3H19v15H6.5A1.5 1.5 0 0 0 5 19.5zM5 19.5A1.5 1.5 0 0 0 6.5 21H19v-3"/></symbol>
  <symbol id="i-demo" viewBox="0 0 24 24"><rect x="3.5" y="4.5" width="17" height="15" rx="2.5"/><path d="M10.5 9.5l4.5 2.5-4.5 2.5z"/></symbol>
  <symbol id="i-codigo" viewBox="0 0 24 24"><path d="M8.5 8l-4 4 4 4M15.5 8l4 4-4 4M13.5 6l-3 12"/></symbol>
  <symbol id="i-img" viewBox="0 0 24 24"><rect x="3.5" y="4.5" width="17" height="15" rx="2.5"/><circle cx="9" cy="10" r="1.5"/><path d="M4 17l5-4.5 4 3 3-2.5 4 3.5"/></symbol>
  <symbol id="i-outro" viewBox="0 0 24 24"><path d="M6 3.5h8l4 4v13H6zM14 3.5v4h4"/></symbol>
  <symbol id="i-chev" viewBox="0 0 24 24"><path d="M9 6l6 6-6 6"/></symbol>
  <symbol id="i-menu" viewBox="0 0 24 24"><path d="M4 7h16M4 12h16M4 17h16"/></symbol>
  <symbol id="i-tema" viewBox="0 0 24 24"><circle cx="12" cy="12" r="8"/><path d="M12 4a8 8 0 0 1 0 16z" fill="currentColor"/></symbol>
  <symbol id="i-copy" viewBox="0 0 24 24"><rect x="8.5" y="8.5" width="11" height="11" rx="2"/><path d="M15.5 8.5v-2a2 2 0 0 0-2-2h-7a2 2 0 0 0-2 2v7a2 2 0 0 0 2 2h2"/></symbol>
  <symbol id="i-ext" viewBox="0 0 24 24"><path d="M13 5h6v6M19 5l-8 8M18 14v4a1.5 1.5 0 0 1-1.5 1.5h-9A1.5 1.5 0 0 1 6 18V9a1.5 1.5 0 0 1 1.5-1.5H10"/></symbol>
  <symbol id="i-busca" viewBox="0 0 24 24"><circle cx="11" cy="11" r="6.5"/><path d="M16 16l4 4"/></symbol>
</defs></svg>

<header class="top">
  <button class="btn icon menu" id="menu" aria-label="Abrir navegação"><svg class="ic"><use href="#i-menu"/></svg></button>
  <a class="brand" href="#/"><b class="mark">{ }</b><span>__TITULO__</span></a>
  <div class="grow"></div>
  <label class="search"><svg class="ic"><use href="#i-busca"/></svg><input id="busca" type="search" placeholder="Buscar arquivos e pastas" autocomplete="off" aria-label="Buscar arquivos e pastas"></label>
  <button class="btn icon" id="tema" aria-label="Alternar tema claro e escuro"><svg class="ic"><use href="#i-tema"/></svg></button>
</header>
<div class="scrim" id="scrim"></div>

<div class="shell">
  <nav class="side" id="nav" aria-label="Pastas do repositório"><ul class="tree" id="arvore"></ul></nav>
  <main id="main"><noscript>Ative o JavaScript para navegar pelo repositório.</noscript></main>
</div>

<script id="dados" type="application/json">__DADOS__</script>

<script defer src="https://cdnjs.cloudflare.com/ajax/libs/marked/4.3.0/marked.min.js"></script>
<script defer src="https://cdnjs.cloudflare.com/ajax/libs/highlight.js/11.9.0/highlight.min.js"></script>
<script defer src="https://cdnjs.cloudflare.com/ajax/libs/KaTeX/0.16.9/katex.min.js"></script>
<script defer src="https://cdnjs.cloudflare.com/ajax/libs/KaTeX/0.16.9/contrib/auto-render.min.js"></script>

<script>
(function () {
  'use strict';

  /* ---------- dados e utilitários ---------- */
  const $ = (s, r = document) => r.querySelector(s);
  const RAIZ = JSON.parse($('#dados').textContent);
  const ORDEM_TIPOS = ['guia', 'demo', 'codigo', 'img', 'outro'];
  const ROTULO = { guia: 'Guia', demo: 'Demonstração', codigo: 'Código', img: 'Imagem', outro: 'Arquivo' };
  const NOME_TIPO = {
    guia: ['guia', 'guias'], demo: ['demonstração', 'demonstrações'], codigo: ['código', 'códigos'],
    img: ['imagem', 'imagens'], outro: ['arquivo', 'arquivos']
  };
  const esc = s => String(s).replace(/[&<>"]/g, c => ({ '&': '&amp;', '<': '&lt;', '>': '&gt;', '"': '&quot;' }[c]));
  const norm = s => s.normalize('NFD').replace(/[\u0300-\u036f]/g, '').toLowerCase();
  const href = p => '#/' + p.split('/').filter(Boolean).map(encodeURIComponent).join('/');
  const rot = (k, n) => NOME_TIPO[k][n === 1 ? 0 : 1];
  const icone = n => `<svg class="ic"><use href="#i-${n}"/></svg>`;

  const porCaminho = new Map();
  (function indexar(n, pai) {
    n.pai = pai;
    porCaminho.set(n.path, n);
    (n.children || []).forEach(c => indexar(c, n));
  })(RAIZ, null);

  function contar(n) {
    if (n.cont) return n.cont;
    const c = {};
    if (n.tipo === 'file') c[n.kind] = 1;
    else n.children.forEach(f => { const x = contar(f); for (const k in x) c[k] = (c[k] || 0) + x[k]; });
    return n.cont = c;
  }
  const pills = c => ORDEM_TIPOS.filter(k => c[k]).map(k => `<span class="pill k-${k}"><i></i>${c[k]} ${rot(k, c[k])}</span>`).join('');
  const resumo = c => ORDEM_TIPOS.filter(k => c[k]).map(k => `${c[k]} ${rot(k, c[k])}`).join(' · ');

  /* ---------- estado ---------- */
  let ATUAL = '';              // caminho selecionado (pasta ou arquivo)
  let ARQUIVO = null;          // arquivo aberto no visualizador
  let PASTA_ANTERIOR = null;
  let BUSCA = '';
  const ABERTAS = new Set();

  /* ---------- árvore lateral ---------- */
  function ramo(n, q) {
    if (n.tipo === 'file') {
      if (q && !norm(n.nome + ' ' + n.arq).includes(q)) return '';
      return `<li><a class="row file k-${n.kind}${n.path === ATUAL ? ' on' : ''}" href="${href(n.path)}">${icone(n.kind)}<span>${esc(n.nome)}</span></a></li>`;
    }
    const filhos = n.children.map(c => ramo(c, q)).join('');
    const bate = q && norm(n.nome + ' ' + n.arq).includes(q);
    if (q && !filhos && !bate) return '';
    const aberta = q ? true : ABERTAS.has(n.path);
    return `<li class="${aberta ? 'open' : ''}"><div class="row${n.path === ATUAL ? ' on' : ''}">` +
      `<button class="tog" data-t="${esc(n.path)}" aria-label="Expandir ${esc(n.nome)}" aria-expanded="${aberta}">${icone('chev')}</button>` +
      `<a class="name" href="${href(n.path)}">${icone('dir')}<span>${esc(n.nome)}</span></a></div><ul>${filhos}</ul></li>`;
  }
  function desenharArvore() {
    const q = norm(BUSCA.trim());
    const filhos = RAIZ.children.map(c => ramo(c, q)).join('');
    $('#arvore').innerHTML =
      `<li><a class="row home${ATUAL === '' ? ' on' : ''}" href="#/">${icone('dir')}<span>Início</span></a></li>` +
      (filhos || '<li class="none">Nada encontrado.</li>');
    if (!q) { const on = $('#arvore .on'); if (on && on.scrollIntoView) on.scrollIntoView({ block: 'nearest' }); }
  }

  /* ---------- páginas ---------- */
  function migalhas(pasta, arq) {
    const cadeia = [];
    for (let a = pasta; a; a = a.pai) cadeia.unshift(a);
    const itens = cadeia.map((a, i) => {
      const rotulo = a === RAIZ ? 'Início' : a.nome;
      const ultimo = i === cadeia.length - 1 && !arq;
      return ultimo ? `<span aria-current="page">${esc(rotulo)}</span>` : `<a href="${href(a.path)}">${esc(rotulo)}</a>`;
    });
    if (arq) itens.push(`<span aria-current="page">${esc(arq.nome)}</span>`);
    return `<nav class="crumbs" aria-label="Caminho">${itens.join('<span class="sep">/</span>')}</nav>`;
  }

  function card(p) {
    const sub = p.children.filter(x => x.tipo === 'dir').length;
    return `<a class="card" href="${href(p.path)}"><span class="card-top">${icone('dir')}<strong>${esc(p.nome)}</strong></span>` +
      `<span class="path">${esc(p.arq)}/${sub ? ' · ' + sub + (sub === 1 ? ' pasta' : ' pastas') : ''}</span>` +
      `<span class="pills">${pills(contar(p))}</span></a>`;
  }

  function visualizador(arquivos, ativo) {
    const grupos = ORDEM_TIPOS.map(k => [k, arquivos.filter(f => f.kind === k)]).filter(g => g[1].length);
    const abas = grupos.map(([k, lista]) => {
      const alvo = k === ativo.kind ? ativo : lista[0];
      return `<a class="tab k-${k}" role="tab" aria-selected="${k === ativo.kind}" href="${href(alvo.path)}">${icone(k)}${ROTULO[k]}${lista.length > 1 ? ` <small>${lista.length}</small>` : ''}</a>`;
    }).join('');
    const irmaos = arquivos.filter(f => f.kind === ativo.kind);
    const chips = irmaos.length > 1
      ? `<div class="chips">${irmaos.map(f => `<a class="chip" href="${href(f.path)}"${f === ativo ? ' aria-current="true"' : ''}>${esc(f.nome)}</a>`).join('')}</div>` : '';
    return `<div class="tabs" role="tablist">${abas}</div><section class="viewer" id="viewer">${chips}<div class="vbar" id="vbar"></div><div class="vbody" id="vbody"></div></section>`;
  }

  function pagina(pasta, arq) {
    const raiz = pasta === RAIZ;
    const subs = pasta.children.filter(x => x.tipo === 'dir');
    const arquivos = pasta.children.filter(x => x.tipo === 'file');
    let h = migalhas(pasta, arq);
    h += `<header class="head"><h1>${esc(pasta.nome)}</h1>${raiz && RAIZ.desc ? `<p class="sub">${esc(RAIZ.desc)}</p>` : ''}<p class="tally">${resumo(contar(pasta))}</p></header>`;
    const mostrarCards = subs.length && !arq;
    if (mostrarCards) h += `<h2 class="sec">${raiz ? 'Conteúdo' : 'Subpastas'}</h2><div class="cards">${subs.map(card).join('')}</div>`;
    if (arquivos.length && (arq || !raiz)) {   // na página inicial, só os cards (arquivos da raiz abrem pela barra lateral)
      const ativo = arq || ORDEM_TIPOS.map(k => arquivos.find(f => f.kind === k)).find(Boolean);
      if (mostrarCards) h += `<h2 class="sec">Arquivos desta pasta</h2>`;
      h += visualizador(arquivos, ativo);
      ARQUIVO = ativo;
    } else ARQUIVO = null;
    return h;
  }

  /* ---------- visualizador ---------- */
  const botao = (acao, texto, ic) => `<button class="btn" data-act="${acao}">${icone(ic)}<span>${texto}</span></button>`;

  function preencher(f) {
    const barra = $('#vbar'), corpo = $('#vbody');
    if (!barra) return;
    const kb = (f.tamanho / 1024).toFixed(1).replace('.', ',') + ' KB';
    let info = kb, acoes = '';
    if (f.kind === 'demo') acoes = botao('abrir', 'Abrir em nova aba', 'ext');
    else if (f.kind !== 'img') acoes = botao('copiar', 'Copiar', 'copy');
    const texto = f.conteudo || '';
    if (f.kind === 'codigo' || f.kind === 'outro') {
      const n = texto.trim() ? texto.replace(/\n$/, '').split('\n').length : 0;
      info = `${n} linhas · ${kb}`;
    }
    barra.innerHTML = `<span class="vpath" title="${esc(f.path)}">${esc(f.path)}</span><span class="vinfo">${info}</span><span class="vact">${acoes}</span>`;

    if (f.kind === 'img') { corpo.innerHTML = `<div class="imgwrap"><img src="${f.uri}" alt="${esc(f.nome)}"></div>`; return; }
    if (!texto.trim()) { corpo.innerHTML = '<p class="empty">Este arquivo está vazio.</p>'; return; }

    if (f.kind === 'demo') {
      corpo.innerHTML = '<iframe class="frame" title="' + esc(f.nome) + '" sandbox="allow-scripts allow-modals allow-forms allow-popups"></iframe>';
      $('iframe', corpo).srcdoc = texto;
      return;
    }
    if (f.kind === 'guia') {
      const html = window.marked ? window.marked.parse(texto, { mangle: false, headerIds: false }) : '<pre>' + esc(texto) + '</pre>';
      corpo.innerHTML = '<article class="prose">' + html + '</article>';
      corpo.querySelectorAll('table').forEach(t => { const w = document.createElement('div'); w.className = 'table-wrap'; t.replaceWith(w); w.append(t); });
      if (window.hljs) corpo.querySelectorAll('pre code').forEach(el => { try { window.hljs.highlightElement(el); } catch (e) { /* mantém texto simples */ } });
      if (window.renderMathInElement) {
        try {
          window.renderMathInElement(corpo, { delimiters: [{ left: '$$', right: '$$', display: true }, { left: '$', right: '$', display: false }], throwOnError: false });
        } catch (e) { /* mantém texto simples */ }
      }
      return;
    }
    // código e outros arquivos de texto
    let realce = esc(texto);
    if (window.hljs) {
      try { realce = f.ext === 'c' ? window.hljs.highlight(texto, { language: 'c' }).value : window.hljs.highlightAuto(texto).value; } catch (e) { /* mantém texto simples */ }
    }
    const linhas = texto.replace(/\n$/, '').split('\n').length;
    const calha = Array.from({ length: linhas }, (_, i) => i + 1).join('\n');
    corpo.innerHTML = `<div class="code"><pre class="ln" aria-hidden="true">${calha}</pre><pre class="src"><code class="hljs">${realce}</code></pre></div>`;
  }

  async function copiar(btn) {
    const texto = ARQUIVO.conteudo || '';
    try { await navigator.clipboard.writeText(texto); }
    catch (e) {
      const t = document.createElement('textarea'); t.value = texto; document.body.append(t); t.select();
      try { document.execCommand('copy'); } catch (_) { /* sem permissão */ }
      t.remove();
    }
    const rotuloBtn = $('span', btn), antes = rotuloBtn.textContent;
    rotuloBtn.textContent = 'Copiado';
    setTimeout(() => { rotuloBtn.textContent = antes; }, 1500);
  }
  function abrirEmAba() {
    const url = URL.createObjectURL(new Blob([ARQUIVO.conteudo], { type: 'text/html' }));
    window.open(url, '_blank');
    setTimeout(() => URL.revokeObjectURL(url), 60000);
  }

  /* ---------- roteamento ---------- */
  function renderizar() {
    const p = decodeURIComponent(location.hash.replace(/^#\/?/, '')).replace(/\/+$/, '');
    const no = porCaminho.get(p) || RAIZ;
    const pasta = no.tipo === 'file' ? no.pai : no;
    const arq = no.tipo === 'file' ? no : null;
    ATUAL = no.path;
    for (let a = pasta; a; a = a.pai) ABERTAS.add(a.path);
    desenharArvore();
    $('#main').innerHTML = pagina(pasta, arq);
    if (ARQUIVO) preencher(ARQUIVO);
    document.title = (no === RAIZ ? '' : no.nome + ' · ') + RAIZ.nome;
    if (pasta !== PASTA_ANTERIOR) window.scrollTo(0, 0);
    PASTA_ANTERIOR = pasta;
  }

  /* ---------- eventos ---------- */
  $('#nav').addEventListener('click', e => {
    const tog = e.target.closest('.tog');
    if (tog) {
      const caminho = tog.dataset.t;
      if (ABERTAS.has(caminho)) ABERTAS.delete(caminho); else ABERTAS.add(caminho);
      desenharArvore();
      return;
    }
    if (e.target.closest('a')) document.body.classList.remove('nav-open');
  });
  $('#main').addEventListener('click', e => {
    const b = e.target.closest('[data-act]');
    if (!b || !ARQUIVO) return;
    if (b.dataset.act === 'copiar') copiar(b); else abrirEmAba();
  });
  $('#busca').addEventListener('input', e => { BUSCA = e.target.value; desenharArvore(); });
  $('#menu').addEventListener('click', () => document.body.classList.toggle('nav-open'));
  $('#scrim').addEventListener('click', () => document.body.classList.remove('nav-open'));
  $('#tema').addEventListener('click', () => {
    const raiz = document.documentElement;
    const escuro = window.matchMedia('(prefers-color-scheme:dark)').matches;
    const novo = (raiz.dataset.theme || (escuro ? 'dark' : 'light')) === 'dark' ? 'light' : 'dark';
    raiz.dataset.theme = novo;
    try { localStorage.setItem('tema', novo); } catch (e) { /* sem armazenamento */ }
  });
  window.addEventListener('hashchange', renderizar);
  document.addEventListener('DOMContentLoaded', renderizar);
  if (document.readyState !== 'loading') renderizar();
})();
</script>
</body>
</html>
'''


# ---------------------------------------------------------------------------
# Execução
# ---------------------------------------------------------------------------
def main():
    raiz = Path(sys.argv[1]).resolve() if len(sys.argv) > 1 else Path(__file__).resolve().parent
    if not raiz.is_dir():
        sys.exit(f"Pasta não encontrada: {raiz}")

    arvore = construir(raiz, raiz)
    arvore["desc"] = DESCRICAO
    dados = json.dumps(arvore, ensure_ascii=False, separators=(",", ":"))
    dados = dados.replace("</", "<\\/").replace("<!--", "<\\u0021--")  # evita fechar o <script> sem querer

    html = TEMPLATE.replace("__TITULO__", TITULO).replace("__DADOS__", dados)
    saida = raiz / "index.html"
    saida.write_text(html, encoding="utf-8")

    def contar(no, acc):
        if no["tipo"] == "file":
            acc[no["kind"]] = acc.get(no["kind"], 0) + 1
        else:
            for f in no["children"]:
                contar(f, acc)
        return acc

    c = contar(arvore, {})
    print(f"index.html gerado em {saida} ({saida.stat().st_size / 1024:.0f} KB)")
    print("Arquivos incluídos:", ", ".join(f"{v} {k}" for k, v in sorted(c.items())))


if __name__ == "__main__":
    main()
