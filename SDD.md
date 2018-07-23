# Programa de modelagem 3D de geologia
## Software Design Document

### 1.	DESCRIÇÃO
Programa de modelagem 3D de geologia, com poucos pré-requisitos para uso inicial (fácil de usar), que permita compor um modelo a partir de desenhos de perfis geológicos em 2D. A complexidade geológica virá do usuário, e não do computador. Com o modelo pronto, será possível extrair perfis 2D de qualquer lugar do modelo.
### 2.	CARACTERÍSTICAS PRINCIPAIS
#### O que o software VAI ser/fazer:
1.	Código aberto, disponibilizado na internet. Código e interface em inglês;
2.	Baseado em Windows, desktop;
3.	Uso simples e intuitivo (desde a instalação até o produto final, passando pelo processo de desenho). 
4.	Conceito de “começar simples, terminar complexo”: a partir de poucos comandos (3 ou 4 ferramentas principais), formas geométricas simples e interpolação entre elas, o usuário poderá progressivamente refinar o modelo até terminar com uma geologia complexa e detalhada;
5.	Fazer atalhos de teclado para as principais funções. De modo que usuários experientes possam aumentar a velocidade de processos repetitivos.
6.	Permitir o desenho de perfis geológicos em planos 2D, com uso de polilinhas e desenho mão livre. Será possível desenhar também na vista 3D;
7.	A partir de no mínimo 2 perfis (não necessariamente paralelos), o software fará automaticamente a interpolação direta entre camadas. Toda interpolação será no máximo uma reta entre 2 pontos ou um plano entre 3 pontos (mais do que 3 pontos geram um TIN – Triangular Irregular Network).
8.	Depois da primeira interpolação (primeiro volume 3D gerado), o usuário poderá desenhar novos perfis dentro do volume 3D para refinar o modelo. Poderão ser feitos quantos perfis forem necessários em contínuas iterações de refinamento. O software sempre atualizará o modelo com os novos perfis.
9.	Extrair perfis 2D a partir de qualquer local do modelo, com qualquer orientação.

#### O que o software NÃO vai ser/fazer:
1.	Software online ou baseado em smartphone/tablet;
2.	Interpolação automática de camadas geológicas complexas. 
3.	Exigir georreferenciamento do local de estudo para iniciar um desenho;
4.	Exigir um modelo digital de terreno ou superfície 3D para iniciar um desenho;
5.	Exigir dados de sondagens para iniciar um desenho;

### 3.	PROBLEMA INICIAL / MOTIVAÇÃO / SITUAÇÃO ATUAL
Softwares para modelagem 3D de geologia em geral são:
1.	Caros e específicos para determinadas indústrias (mineração ou petróleo);
2.	Os gratuitos ou baratos são limitados e não permitem uso profissional para elaboração de modelos geológicos e produtos finais (perfis geológicos);
3.	Difíceis de usar, em geral exigem muitos pré-requisitos para primeiro uso: habilidades ou conhecimento de desenho e/ou modelagem 3D, métodos de interpolação, georreferenciamento, dados de sondagens, modelo digital de terreno. Softwares não dedicados a modelagem geológica mas que fazem modelagem 3D necessitam de um longo tempo para aprendizado, e não são padrão nas empresas que trabalham com alguma área relacionada à geologia.

O AutoCAD, software padrão de muitas empresas (ambiental e engenharia, pelo menos) é direcionado prioritariamente à desenho 2D, pois a função 3D é pesada e não é de domínio comum mesmo entre desenhistas profissionais. Além do mais, o AutoCAD não é otimizado para os elementos que constam em desenhos de geologia, como formas curvas e preenchimentos (hachuras ou cores sólidas), além de não funcionar bem para iterações e refinamentos progressivos e frequentes (em geral, partes inteiras de um desenho devem ser refeitas a cada nova informação acrescentada ou correção feita).
O advento do BIM (Building Information Modeling) pode servir de incentivo para modelagem 3D de geologia. Alguns países estão bem avançados com relação à modelagem 3D de geologia para uso geral, como a Grã-Bretanha.

### 4.	REQUISITOS DO USUÁRIO
O que usuário PRECISA:
1.	Ter conhecimento básico do que é um perfil geológico;
2.	Ter uma ideia geral do modelo geológico que está se tentando executar, bem como os conceitos e o contexto geológico do local que se tenta representar (por exemplo: se é um local com sedimentos, de que forma as camadas vão se intercalar ou interdigitar – em formato de “espinhas de peixe”, canais, lentes etc).

O que o usuário NÃO PRECISA:
1.	Ser desenhista (ou “cadista”) profissional, ou ter habilidades e conhecimentos de softwares de desenho 2D e modelagem 3D;

### 5.	NÃO FAZER / FUNÇÕES FUTURAS
A primeira versão do software NÃO vai ter (mas terá no futuro). 
Uma vez que o software esteja pronto, estas serão as primeiras características as serem implementadas.
1.	Versões para Linux e Mac;
2.	Georreferenciamento (para iniciar um desenho, para importar e exportar);
    1.	Possibilidade de se fazer um referenciamento simples: por exemplo selecionar 4 pontos e definir a que coordenadas UTM estes pontos correspondem, apenas para poder lançar pontos com coordenadas, como sondagens por exemplo. Esta opção mostraria um aviso ao usuário de que este tipo de referenciamento pode causar imprecisões nas coordenadas. Pode-se também definir que o ponto 0,0,0 equivale a um ponto específico de um projeto, como 150.000, 250.000, 10 por exemplo.
3.  Importação e exportação para arquivos SHP, DXF, KMZ etc;
4.	Inclusão de estruturas/descontinuidades da rocha (foliação, fraturas, falhas, juntas etc);
5.	Estereograma para mostrar comportamento das camadas em determinado ponto;
6.	Identificação de elementos estruturais de dobras (charneira, eixo etc);
7.	Exportação para visualização em PDF 3D e página HTML;
8.	Importação de formas geométricas simples de arquivos do AutoCAD, para representar muros, pilares de OAEs, túneis, taludes etc. No caso de taludes, cruzamento com dados de descontinuidades para mostrar possibilidade cinemáticas de ocorrências de rupturas em cunhas, planos e tombamentos (neste caso, mostrar bloco diagrama simples, em formato de talude, com bermas e bancadas, estereograma e estereograma em 3D (no caso do estereograma 3D, ver o DIPS);
 	 

9.	Módulo para desenho de palitos de sondagem: abrir janela com campos para preenchimento dos dados de sondagem e configuração dos aspecto do palito.

### 6.	CARACTERÍSTICAS DETALHADAS
1.	Instalação simples, somente um arquivo de download para instalação;
2.	Vista 3D sempre em projeção ortogonal (isométrica);
3.	Possibilidade de editar interface (cor, posicionamento de janelas e menus) e comandos (o que faz cada botão e atalho);
4.	Janela do programa irá conter:
    1.	Menus de topo (ARQUIVO, EDITAR, VISUALIZAR etc);
    2.	Tela principal: vista 3D
    3.	Todas as ferramentas de desenho e edição em menus laterais;
    4.	Será possível ter várias janelas, cada uma com uma vista. Por exemplo, uma janela com a vista isométrica, outra com a vista XZ do modelo e outra com a vista YZ. Assim, pode-se desenhar uma camada na vista XZ e visualizar e ajustar esta mesma camada na vista YZ. ```INSERIR GIF MOSTRANDO O FUNCIONAMENTO DESTA FUNÇÃO ```
5.	Vista 3D inicial mostrará:
    1.	um ícone 3D de eixos X (vermelho), Y (verde) e Z (azul);
    2.	um cubo de visualização igual ao do AutoCAD (mostrando topo, frente, controles de girar a vista etc) no canto superior direito;
    3.	um cubo de 100 x 100 x 100 m, para início de desenho, com escalas de cota e extensão em metros, com um dos vértices do cubo na coordenada 0,0,0; Este cubo inicial será editável a qualquer momento, em termos de extensões e escala. Ele irá será a base para todo o modelo e irá conter toda a geometria desenhada.
    4.	Curvas de nível podem ser ativadas/desativadas e pode-se editar espaçamento entre curvas e mostrar curvas mestras;

### 7.	FUNCIONAMENTO
#### 1.	Navegação:
  1.	Clique esquerdo: desenhar;
  2.	Clique direito: propriedades e funções adicionais;
  3.	Barra de espaço + mover mouse (sem clicar botão): pan vista igual ao do QGIS (arrastar a vista na horizontal/vertical/diagonal) OU função invertida com o clique da roda do mouse;
  4.	Clique da roda do mouse: girar/rotacionar/órbita da vista (orbitar em torno do centro do cubo);
  5.	Roda do mouse: zoom (para posição do cursor do mouse);
  6.	Sempre haverá, saindo do cursor, uma reta vertical indo até o “chão” para o usuário sempre ter uma noção de onde, no espaço 3D, está o cursor;

#### 2.	Atalhos (em geral copiados do AutoCAD).
  1.	Barra de espaço/enter: repete último comando;
  2.	L: linha
  3.	PL: polilinha;
  4.	H: desenho mão livre (“H” de “hand”);
  5.	U/Ctrl + Z: desfazer;
  6.	I: interpolar (ver item 3 abaixo);
  7.	T: terreno (ver item 3 abaixo);
  8.	F3: liga/desliga SNAP (definir vários modos de SNAP como no AutoCAD: para vértice, perpendicular, mais próximo etc);
  9.	F8: liga/desliga travar desenho na ortogonal;	

#### 3.	Edição/Desenho:
  1.	Possibilidade de selecionar por vértice, linha ou plano;
  2.	A ferramenta padrão será sempre a polilinha. Com o Ctrl pressionado, o usuário poderá desenhar uma reta ortogonal a qualquer um dos eixos X, Y e Z. ```INSERIR GIF MOSTRANDO O FUNCIONAMENTO DESTA FUNÇÃO```
  3.	Possibilidade de se carregar uma imagem para ficar no fundo. Como por exemplo um perfil desenhado a mão e escaneado, para servir de base para o desenho. Uma vez posicionado no espaço 3D, o plano contendo a imagem irá rotacionar junto com o todo o desenho.
  4.	Se o usuário desenhar dois perfis e no Perfil A houver a camada 1, e no Perfil B, não, o software irá interpolar todas as camadas, fazendo a camada 1 sumir gradualmente do Perfil A para o Perfil B. ```INSERIR GIF MOSTRANDO O FUNCIONAMENTO DESTA FUNÇÃO
  5.	Para desenho de perfil em 2D, incluir um menu para seleção de quais eixos se quer desenhar (exemplo: XY, XZ, YZ ou planos inclinados). Com isso, ao posicionar o mouse sobre o modelo 3D, uma pequena janela junto ao cursor vai mostrar uma prévia da fatia a ser mostrada no perfil 2D. ```INSERIR GIF DO EXEMPLO DO QT MOSTRANDO ESTA FUNÇÃO


#### 4.	Ferramentas/Comandos Especiais.
  1.	Terreno: se ativo, qualquer linha que o usuário desenhar acima da superfície do terreno irá modificar a superfície. Isto irá possibilitar um esboço rápido em 2D de um perfil contendo um morro, uma depressão (lago, canal de rio etc) ou superfícies irregulares, que poderão ser expandidos em outras direções para formar um volume 3D;
  2.	Interpolar: dependendo do modo de seleção, irá interpolar entre elementos selecionados: 2 vértices = 1 linha, 2 linhas = 1 plano (TIN), 2 planos = 1 sólido (vários TINs);
  3.	Otimizar desenho mão livre (2D) para polilinha ou spline: se ativada esta função, o usuário poderá desenhar uma forma complexa com a ferramenta de mão livre, e o software irá otimizar a forma para um spline ou para polilinhas (segmentos de reta). No caso de polilinhas, haverá opção para escolher, de 0 a 10, qual o grau de otimização (0 poucos segmentos de reta, 10 muitos segmentos).

### 8.	REFERÊNCIAS BIBLIOGRÁFICAS
Incluir referências de trabalhos acadêmicos com pesquisa em algoritmos de interpolação para geração de modelo geológico, sites de softwares de modelagem etc.
