/header q   CLZ �   �1.0    O   resource::Chunk A?   - �LODArray" �LOD  "  ;S  % 
 ES �Parameters"  �     ����/lod0 @	  CLZ �  �1.0    P   meta::ObjectPointer A<   5  	$   S    ��  graphics::Shader գ  resourceK �]      S 6  �   "  Properties
 &y Q  1Bas1 (@ 1 Z B �    TexturZ / X 
p   Ren� 8tat�  �   '  VertexBuff `uint32  O   ;�� FilePath storag�   @   	ZKtampL �# 	 ?  |t    � �pbasic::U �  Geometry"  Q�Fragment" &�D XInput� �HADER_SOURCE_INPUT� 3 ?Out4 	?OUT5  2Max8 � ' � � #/�LineArray `String S�  � �O// - M� !m  �� tonemapper v� " ss	� Y
f B�   #version 130    �   varying vec2 uv; " 1  / �void main() �{< �       uv = gl_MultiTexCoord0.xy; # ' �gl_Posit� �= ftransform(); Y 4} � /8 "  < /�< �x  6   �Y +Df�F� [begin] � Y�NP   - Qexten �GL_ARB_t��_rectangle : enable S �   %   uni� sampler2DRect i�H ?; - � luminance-  r- �float brightness;�" �contrast; "�
  �gamma; #= Qexpos $�   �ye_adapta4; %&�'" 1(  I CGetEl E() )�S*   Jls 3 = !=2D(5,w �(0.5, 0.5)).x;�dR ereturn� j*(1.0-� u)+0.12*# 
 2 )/(� �+0.0001)); ,-� .	 /��vec3 ApplyT(( Ev) 01,�A = 0.15; 2 B ]50; 3 C8 M0; 4 D ]20; 5 E ]02; 6 F T30; 7�  �4e�((v*(A*v+C*B)+D*E)/  �F))-E/F; 95:O ;Y `)�oend] =� Y>?� @2SA   7�PXcolor/ �(��, uv).xyz; B�	 ? # C  G 	� H); D6 Ew6 '*=�YF    )+=�[G   v  � s( H      2pow� 2.x,�O), I% y% J�% z% C); K�� |
C� 42 �, 1.0); L�MN O�  =,[FlagsD
QH  T R� =@   URO   WX $X��Y   Z   [  d2# �
�FaceCullingMod�!EN/�TATE_FACE_CULLINGr �FrontPolygon< 	�POLYGON_MODE< OBack; $�DepthTestE�sd bool R @Func�Z �TEST_FUNCTION[ Writing^ � � lW d� L� OlendQ  [oFactor[ �BLENDING�<TOR_ aDestin�H "_AlphaW W"> �Threshold real �v�\   ����]�^ _! `�a b #c �  f g�h� ?i j� �?�  � #� � NTypes�PROPERTY_TYP�TValue�
SOjEvalua�Q gEVALUA�k�  5m�
Z� �n� qo   p  �
T� �q� Sr   s�U� �t� u�&V� �w� Sx   y�Y� �z� S{   |+Z� �}� S~   �  � �c  \�
Am��S���� \;E  �
C �C r$C  f|
@ �@ u� �C �C  �AC  '
�I �I  //,I  )
	d) M�?  � /� ��w�Parameter<�TEXTURE_PARAMETER���-���� /coffee/import/� ts/null.� �g ���04 "�8�8��8�g ��           