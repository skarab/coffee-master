/header q   CLZ �   �1.0    O   resource::Chunk A?   - �LODArray" �LOD  "  ;S  % 
 ES �Parameters"  �     ����/lod0 )	  CLZ \  �1.0    P   meta::ObjectPointer A<   5  	$   S    ��  graphics::Shader �~  resourceK �]      S 6  �   �
  Properties
 &y Q  1Bas1 (@ 1 Z B �    TexturZ / X 
p   Ren� 8tat�  �   '  VertexBuff `uint32  O   ;�� FilePath storag�   @   	ZKtampL �# 	 ?  |t�
    � �pbasic::U �  Geometry"  Q�Fragment" &�D XInput� �HADER_SOURCE_INPUT� 3 ?Out4 	?OUT5  2Max8 � ' � � #/�LineArray `String S�  � �O// - M� !m  �� tonemapper v� " ss	� Y
f�      #version 130    �   varying vec2 uv; " 1  / �void main() �{< �       uv = gl_MultiTexCoord0.xy; # ' �gl_Posit� �= ftransform(); Y 4} � /8 "  < /�< �S  3   �Y +Df�F� [begin] � Y�NP   - Qexten �GL_ARB_t��_rectangle : enable S �   %   uni� sampler2DRect i�H ?; - � luminance-  r- �float brightness;�" �contrast; "�
  �gamma; #= Qexpos $�   �ye_adapta4; %&�'" 1(  I CGetEl E() )�S*   Jls 3 = !=2D(5,w �(0.5, 0.5)).x;�dR ereturn� j*(1.0-� u)+0.12*# 
 2 )/(� �+0.0001)); ,-� .	 /��vec3 ApplyT(( Ev) 01� � Jv *=/ ; h  �.x = max(0, -� Y4); 3% y% y% 4% z% z% Z5   1C�(v*(v*6.2+i/ 01.7De06); 678�Y_9   )�oend] :� Y;<� =T>   7� +Xcolor
 l(l�, uv).xyz; ?�	 ? # @�  G 	� H); A6 BR6 '*=hYC    )+=�[D   v  � 7( E  2pow� 2.x,�O), F% y% G�% z% C); H�� W
C� 42 �, 1.0); I�JK L� ?M  �[Flags
NH  T O`Q� v $X $U\�V   W   X  ?2# r
�FaceCullingModn!EN
�TATE_FACE_CULLINGr �FrontPolygon< 	�POLYGON_MODE< OBack; $�DepthTestE�sd bool R @Func�Z �TEST_FUNCTION[ Writing^ � � lW ?� L� OlendQ  6oFactor[ �BLENDING�<TOR_ aDestin�H "_AlphaW W"> �Threshold real �v�Y   ����Z�[ \! ]�^ _ ` a b #c �P   ?f g� �?�  � #� � NTypeN�PROPERTY_TYP�TValue�
.*jEvalua�Q gEVALUA�h� Pi   j�
Z� �k�  1m  �
Q� �n� So   p�R� �q� Sr   sS� �t� u�	�V� �wDSx   y+W� �z� S{   |�  � %c  7�
Am}`S���� \;E  ��
C ~C o�C  f|
@ @ r� �C �C  �AC  
�I �I  //,I  )
	d) M�?  � /� ��w�Parameter�TEXTURE_PARAMETER���-���� /coffee/import/� ts/null.� �g ���04 "�8�8��8�g ��           