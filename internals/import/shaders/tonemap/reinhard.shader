/header q   CLZ �   �1.0    O   resource::Chunk A?   - �LODArray" �LOD  "  ;S  % 
 ES �Parameters"  �     ����/lod0 �  CLZ �  �1.0    P   meta::ObjectPointer A<   5  	$   S    �  graphics::Shader ��  resourceK �]      S 6  �   s
  Properties
 &y Q  1Bas1 (@ 1 Z B �    TexturZ / X 
p   Ren� 8tat�  �   '  VertexBuff `uint32  O   ;�� FilePath storag�   @   	ZKtampL �# 	 ?  |to
    � �pbasic::U �  Geometry"  Q�Fragment" &D XInput� �HADER_SOURCE_INPUT� 3 ?Out4 	?OUT5  2Max8 � ' � � #/�LineArray `String S�  � �O// - M� !m  �� tonemapper v� " ss	� Y
f�      #version 130    �   varying vec2 uv; " 1  / �void main() �{< �       uv = gl_MultiTexCoord0.xy; # ' �gl_Posit� �= ftransform(); Y 4} � /8 "  < /�< ��  0   �Y +Df�F� [begin] � Y�NP   - Qexten �GL_ARB_t��_rectangle : enable S �   %   uni� sampler2DRect i�H ?; - � luminance-  r- �float brightness;�" �contrast; "�
  �gamma; #= Qexpos $�   �ye_adapta4; %&�'" 1(  I CGetEl E() )�S*   Jls 3 = !=2D(5,w �(0.5, 0.5)).x;�dR ereturn� j*(1.0-� u)+0.12*# 
 2 )/(� �+0.0001)); ,-� .	 /��vec3 ApplyT(( Ev) 01� � Jv *=/3; 2� �v/(v+1.0); 3� 4} 5pY_6   )oend] 7� Y89 :�T;   7� �Xcolor� �(��, uv).xyz; <	 ? # =e  G 	 H); >6 ?�6 '*=� L
 )+=[A   v  � s( B      2pow� 2.x, O), C% y% D&% z% C); E�A �	C� 42 ", �F�GH I�   d}[Flags�	Kv D�   M   N��QX $R�S�o   U  �2# �	�FaceCullingMod�!EN�
�TATE_FACE_CULLINGr �FrontPolygon< 	�POLYGON_MODE< OBack; $�DepthTestEsd bool R @Func,Z �TEST_FUNCTION[ Writing^ � � lW �� L� OlendQ  �oFactor[ �BLENDING�<TOR_ aDestin H "_AlphaW W"> �Threshold real �v�V   ����W�X Y! Z[ \ [^ _ ` a�
 ?c  �C�?�   #� � NType��PROPERTY_TYP�TValue=
��jEvalua�Q gEVALUA�e� f�  H
Z� �h� qi   j  
N� �k�  �m�O� �n� So   pwP� �q� r�$S� �t�uV
+T� �w� Sx   y�  � �
c  ��
Amz�S���� \;E  h�
C {C  �8C  f|
@ |@ o�  C }C  �AC  x
:I ~I  //,I  )
	d) MN?   /� ;�w�Parameter��TEXTURE_PARAMETERG�G-G��� /coffee/import/� ts/null.� �g ���04 "8�8��8�g ��           