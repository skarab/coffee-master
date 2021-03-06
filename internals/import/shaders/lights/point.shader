/header q   CLZ �   �1.0    O   resource::Chunk A?   - �LODArray" �LOD  "  ;S  % 
 ES �Parameters"  �     ����/lod0 "  CLZ <+  �1.0    P   meta::ObjectPointer A<   5  	$   S    �h  graphics::Shader �W  resourceK �]      S 6  �   �  Properties
 &y Q  1Bas1 (@ 1 Z B �    TexturZ / X 
p   Ren� 8tat�  �   '  VertexBuff `uint32  O   ;�� FilePath storag�   @   	ZKtampL �# 	 ?  |t�    � �pbasic:: H π  Geometry"  Q�Fragment" &�D XInput� �HADER_SOURCE_INPUT� 3 ?Out4 	?OUT5  2Max8 � ' � � #|/�LineArray `String SH  ��   #version 130 x ��   varying vec2 uv; 
    �3 view_vector; D  �void main() {� �       uv = gl_MultiTexCoord0.xy; # ' g 0 �Color.xyz;    ( �ec4 pos = ftransform();� % �pos.z = 0.9  ; H �gl_Posit=, 3; � 4} � �/8 � � � < /�< S�  k� � %- Qexten �GL_ARB_t�_rectangle : enable �5 �EXT_gpu_s4/  � �// Default helpers  3�PackDepth(float d 5) S   3uareturnl / 2or(/ �/256.0, fract E); � | 1!  R m 5Unp � ~ "~ Z#   $~ ` 1.x*u + Uy); $o %o &u � qNormal( n 5) 'n (an % u+1.0; )a *a +%a � c ,c -c -c .c /c T0   M��ComputeParallax(�,�3eye", bdheight `strengb1� 2�N fcamera�� Fize(_ )� 7 .; o # =s *l % -w  /2� 4X9uv+v S*h; 5Ud}    6T7   pQRGBE(LEv) 8� 9h� �exp = v.w*255.0-128� 1:  `	� ��*exp2(exp); ;�<� =_o#ifdef� d >   [� AAppl�2owsc�, sampler2DRect s" �lI�_softness,�5) ?� @T�  / " = (B �>0.01); A   H�� p*((1.0-/  )+ *� � (� �uv).x); B'C��#endif D61E  �0uni�� �W 3; F�- �. G". Fbase,  � (, hmateri\ _I   "0 v fallof* J� 

93; K. ��p�C;  Lk&  �;" 7!in0Sty; N�' �radius; O� �4; P�QRSD T U�YV   D�') =6
�	I� W�	��* =�
M 
iN Sz); X�O p�� *� 3; Y� / i Z   >< Rixel_i diI 
 z -`Apistance: m(Y *)/�\� � S 8; ]� S^    $//�s BRDF _X	�// Set-up   i�4s `1a  �1: = ���3; b�	�-��); c   8`p 3; ds �specular_� !mi�3Z$),�N �.x)*0.8; e� 7 , > 0> 7 3; f�y @poweB A1.0+�5 'y* p0.9)*24Rg   )��Ashikhmin-Shirley diffuse cal`  �$ h�i�� �*= 4.0*(]�/(23.0*3.14159)) j   "* h	,)9K# 3pow� xD, do�,� ))f�, 5.0)) l(S �H r; m   ,$uFresnelr� - Schlick approxim'n'o�"halfwayX+� 9; p�w��  ^ 
� � 0*10�q� r�  � ,@refl�-� ,�
3; sD �3_faE  �  � �
g 0), � ; � �> v*= step� � S);  u� �++=�0*w*1e ,4H); v�^w   ;�qIllumin�� (Lux) from Ip� (Candela) x
�i> =�p	(a�	(�;h).x; y� zF  �2�
� 8; {@ |  �
}� � �C� �(�
�
�
�
auv), 1T~   
� celse �u 	h C U�   C �
��
�� � �W?�  ��[Flags��H  T ��   �   �   �   �   �X $�X  H��   �   �   �   �   �   �  2# K�FaceCullingModG!EN��TATE_FACE_CULLING� �FrontPolygon< 	�POLYGON_MODE< OBack; $�	QTestE�sd bool b 1Fun	Z �TEST_FUNCTION[ Writing^ \ � lW � L� lcQ  F}[ �BLENDING�<TOR_ CDest�H "_AlphaW W"> �Threshold real �v��   ������� ��i�. �0� � � �" �2�� ?� �� �?�  w #� �NType'�PROPERTY_TYP�TValue(
jEvalua�Q gEVALUA��� S�   ���� ���q�   �  U�� ��� S�   ���� ���  � �8�� ��<S�   �5�� ���S�   �� �� ��� S�   ���� ��� S�   ��� ��� S�   ���� ��� S�   �Z�� ��� S�   �N	��c  �
]& + �	<  � n�R�	G B A Ƨ � � &�  ��  � �� a �cS���� �A� yI �I �� I  ��J �J �J  �� ͎>�r� � ю \/-G
!) ?�"?  � /� �#�t �Xmeter#�TEXTURE_PARAMETER�"��"-�"ө� /coffee/import/� ts/null.� �g �5 �65
�5� �5�53�565�5�� f>���>�s
C>�s��s�g �5 �,5 �	4�4��4�g �4 �/+j_3�3��3�g �3 `/3 "�7��7�g ��           