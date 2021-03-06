/header q   CLZ �   �1.0    O   resource::Chunk A?   - �LODArray" �LOD  "  ;S  % 
 ES �Parameters"  �     ����/lod0 �  CLZ �1  �1.0    P   meta::ObjectPointer A<   5  	$   S    ��  graphics::Shader Չ  resourceK �]      S 6  �   �  Properties
 &y Q  1Bas1 (@ 1 Z B �     TexturZ / X 0Ren� 8tat�  �   '  VertexBuff `uint32  O   ;�� FilePath storag�   @   	ZKtampL �# 	 ?  |t�    � �pbasic:: H π  Geometry"  Q�Fragment" &D XInput� �HADER_SOURCE_INPUT� 3 ?Out4 	?OUT5  2Max8 � ' � � #|/�LineArray `String SH  ��   #version 130 x ��   varying vec2 uv; 
    �3 view_vector; D  �void main() {� �       uv = gl_MultiTexCoord0.xy; # ' g 0 �Color.xyz;    ( �ec4 pos = ftransform();� % �pos.z = 0.9 s;     �gl_Posit=, 3; � 4} � �/8 � � � < /�< S�  u� �P   - Qexten �GL_ARB_t�_rectangle : enable �5 �EXT_gpu_s4/  � �// Default helpers  3�PackDepth(float d 5) S   3uareturnl / 2or(/ �/256.0, fract E); � | 1!  R m 5Unp � ~ "~ Z#   $~ ` 1.x*u + Uy); $o %o &u � qNormal( n 5) 'n (an % u+1.0; )a *a +%a � c ,c -c -c .c /c T0   M��ComputeParallax(�,�3eye", bdheight `strengb1� 2�N fcamera�� Fize(_ )� 7 .; o # =s *l % -w  /2� 4X9uv+v S*h; 5Ud}    6T7   pQRGBE(LEv) 8� 9h� �exp = v.w*255.0-128� 1:  `	� ��*exp2(exp); ;�<� =_o#ifdef� d >   [� AAppl�2owsc�, sampler2DRect s" �lI�_softness,�5) ?� @T�  / " = (B �>0.01); A   H�� p*((1.0-/  )+ *� � (� �uv).x); B'C��#endif D61E  �0uni�� �W 3; F�- �. G". Fbase,  � (, hmateri\ _I   "0 v fallof* J� * vhotspot+ K� 

d3; L1. ��p !;  & �3; Nv" b!in[[ty; OI ' Qapex;" �radius; Q� �;; RDmat4~2to_/ �matrix; SKT�U�VD W� XTYY   DT�) =�
	� �Z+
^* =-
M 
�N 1z);X'O p	� *� 3; \D / �>< Cixelg di|I 
^ z -kj ^   8pistance: �(Y !);� _� � rJ $ `�Sa   O $//s BRDF b�	�// Set-up   i4s cC 1d  �: = �F�3; e|	4-�C); f?�qp �3; g�s �specular_� !mi3�$),kN �.x)*0.8; h� 7 , > 0> 7 u; i   A�	y @poweB A1.0+<5 'y* p0.9)*24tRj   )��Ashikhmin-Shirley diffuse cal`  �$ k�lc� �*= 4.0*(��/(23.0*3.14159)) m   "* �	,z) n   K# 3pow� xD, do�,� ))��, 5.0)) o$S O	H r; p   ,$uFresnelr� - Schlick approxim'q'r+"halfwayT+� 9; s�wa�  ^ 
� � 0*10�t� u�  � ,@refl�-� ,D3; vD �3_faE  �  � g 0), �Q; w  >	> v*= step� � S);  x� �++=�0*w*1e ,4D); y^z   ;�qIllumin�� (Lux) from I�� (Candela) {   h�i> =��	(�e
(�/�D�).x; |   N��Wpace_��! *5 () 1, 1�}� V Q Omin( �~G  �P = 50,= *��o  � I 2xy*(	�� ? 
: *�C5; �&	" +" � �V	�*6(f
,Q ��p�� R M-
k 8; �I�� �  0gl_�Ct	4uv)0T�   
� celse �^u 	h C U�   C ����� � �}?�  ��[Flags�H  "��   �   �   �   �   �   �   �` $�` ��   �   �   �   �   �   �   �  J2# }�FaceCullingMody!EN�TATE_FACE_CULLING� �FrontPolygon< 	�POLYGON_MODE< OBack; $�QTestE
sd bool � 1Fun�Z �TEST_FUNCTION[ Writing^ � � lW J� L� loQ  AFB[ �BLENDING�<TOR_ CDest�H "_AlphaW W"> �Threshold real �v��   ������� �"���. �4� � � �" ���� ?� �� �?�  � #� +NTypeY�PROPERTY_TYP�TValueZ
95jEvalua�Q gEVALUA��� S�   �<�� ���S�   ���� ���S�   �G�� ��mS�   ���� ��mS�   �9�� ��� q�   �  ��� ��� S�   ��
�� ��u � Ȍ �� ��� S�   ��� ��� S�   � �� ��� S�   ф�� ��� S�   �
�� ��� S�   ��
�� ��� S�   ڻ �
 cc  P"
�& + <  � n�$RDG B A ܧ � � &�  ��� �� c �eS���� �	�I   7& 3 M ! � =�?   �
�  *� �>� � � � �D �  n$����2J  � G �G ĝG  ecE �E  �/-e
) U(?  � /� B)�K	 U"Xmeter�(�TEXTURE_PARAMETERN(�N(-N(�
� /coffee/import/� ts/null.� �g � h65
�5� �5�53�565�~#5n� 7f.t�  p �> x/7I]?�?��?� ?�p �?в
�>������g �5 �	,5 �	Q!4�4��4�g �4 
/+�� 3�3��3" g �v
/3 F$j!P/7�/77�          