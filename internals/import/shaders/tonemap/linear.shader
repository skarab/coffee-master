/header q   CLZ �   �1.0    O   resource::Chunk A?   - �LODArray" �LOD  "  ;S  % 
 ES �Parameters"  �     ����/lod0 �  CLZ �  �1.0    P   meta::ObjectPointer A<   5  	$   S    ��  graphics::Shader ��  resourceK �]      S 6  �   Y
  Properties
 &y Q  1Bas1 (@ 1 Z B �    TexturZ / X 
p   Ren� 8tat�  �   '  VertexBuff `uint32  O   ;�� FilePath storag�   @   	ZKtampL �# 	 ?  |tU
    � �pbasic::U �  Geometry"  Q�Fragment" &�D XInput� �HADER_SOURCE_INPUT� 3 ?Out4 	?OUT5  2Max8 � ' � � #/�LineArray `String S�  � �O// - M� !m  �� tonemapper v� " ss	� Y
f�      #version 130    �   varying vec2 uv; " 1  / �void main() �{< �       uv = gl_MultiTexCoord0.xy; # ' �gl_Posit� �= ftransform(); Y 4} � /8 "  < /�< ��  /   �Y +Df�F� [begin] � Y�NP   - Qexten �GL_ARB_t��_rectangle : enable S �   %   uni� sampler2DRect i�H ?; - � luminance-  r- �float brightness;�" �contrast; "�
  �gamma; #= Qexpos $�   �ye_adapta4; %&�'" 1(  I CGetEl E() )�S*   Jls 3 = !=2D(5,w �(0.5, 0.5)).x;�dR ereturn� j*(1.0-� u)+0.12*# 
 2 )/(� �+0.0001)); ,-� .	 /��vec3 ApplyT(( Ev) 0Z1   � )v*35; 2l 3c 4VY_5   )�oend] 6� Y78 9iS:   7i�Xcolorf �(��, uv).xyz; ;	 ? # <K  G 	� H); =6 >�6 '*=�Y?    )+= S
v  � s( A      2pow� 2.x,O), B% y% C% z% C); D�' �	C� 42 �, 1.0); E�FG H� ?I  Jc[Flags{	JH  T K.�   M   N��X !Q�R �/  �2# �	�FaceCullingMod�!ENf
�TATE_FACE_CULLINGr �FrontPolygon< 	�POLYGON_MODE< OBack; $�DepthTestE�sd bool R @FuncZ �TEST_FUNCTION[ Writing^ � � lW �� L� OlendQ  �oFactor[ �BLENDING�<TOR_ aDestinH "_AlphaW W"> �Threshold real �v�U   ����V�W X>�Z [ \ ] ^ _ `�a�
 ?b c� �?�  � #� � NType��PROPERTY_TYP�TValue#
��jEvalua�Q gEVALUA�d�  �f.
Z� �g�  �1i  �	M� �j� Sk   l�N� �m� Sn   o]O� �p� qz
R� �s� {u+S� �v� Sw   x�  � �
c  ��
Amy�S���� \;E  N�
C zC k�C  f|
@ {@ n� �C |C  �AC  ^
 I }I  //,I  )
	d) M4?  ~ /� !�w�Parameters�TEXTURE_PARAMETER-�---�� /coffee/import/� ts/null.� �g p �04 "8�8��8�g ��           