/header q   CLZ �   �1.0    O   resource::Chunk A?   - �LODArray" �LOD  "  ;S  % 
 ES �Parameters"  �     ����/lod0 �  CLZ 1  �1.0    P   meta::ObjectPointer A<   5  	$   S    ��  graphics::Shader չ  resourceK �]      S 6   � �	  Properties
 &y Q  1Bas1 (@ 1 Z B � oTexturZ / X 
p   Ren� 8tat�  �   '  VertexBuff `uint32   I ;�� FilePath storag�   @   	ZKtampL �# 	 ?  |LE $ � �pbasic:: H �F  Geometry"  Q�Fragment" &�D XInput� �HADER_SOURCE_INPUT� 3 ?Out4 	?OUT5  2Max8 � ' � � #B/�LineArray `String S  ��   #version 120 x T�   varying vec2 uv; 
    �3 view_vector; D  �void main() �{           uv = gl_MultiTexCoord0.xy; # ' g 0 �Color.xyz; ( �gl_Posit� �= ftransform(); � 4} � F/8 F"  < /�< �h  :   �P   - Qexten �GL_ARB_t��_rectangle : enable �5 �EXT_gpu_s�4/ � �// Default helpers  �� ��PackDepth(float d 5) � * 3~areturn2 / 2or(/ �/256.0, fract E); �|    m 5Unp � ~  ~ Z!   $~ ` 1.x*u + Uy); "o #o  ; � 3� qNormal( n 5) %n Z&   n % u+1.0; 'a (a )� a � c *c +c -c ,c -c T.   M��ComputeParallax(�,�3eyeE", bdheight `strengb/� 0�N fcamera�� Fize(_ )�1�  ; o # =s *l % -w  /2� 29uv+v S*h; 3d}    4T5   p@RGBEe4 v) 6� Y7   !� �exp = v.w*255.0-128�   	� p�*exp2(exp); 9�:� ;Ao#ifdef� n[� AAppl�2owsc��, sampler2DRect s" �lI�_softness,�5) =� >T�  / " = (B �>0.01); ?   H�� p*((1.0-/  )+ *� � (� �uv).x); @'A~�#endif B61C  g0uni�� irW 4; D6 E�F�GD H� I?J��* =�
	� cyz); K} N I 1+= �L 1/=  �&� �� �Bec4(/ ,H E); NlO!P Q?R  A
Z[FlagsrSH   TD $UD    V   W  z
#
 )�FaceCullingMod�
!ENE	�TATE_FACE_CULLINGn �FrontPolygon< 	�POLYGON_MODE< OBack; $�QTestEtsd bool � @Func�Z �TEST_FUNCTION[ Writing^ �
 � lW z
� L� l�Q  q Fa>[ �BLENDING�<TOR_ pDestina� H "_AlphaW W"> �Threshold real ov�X   ����Y�Z  �# \�^�_ ` a b c�di?�#f# 3?�  � #� � NType��PROPERTY_TYP�TValue�

i�jEvalua�Q gEVALUA�g: �i   ?, c  �	I) � �?  j /� ��j 	Xmeter$�TEXTURE_PARAMETER���-�k�� /coffee/import/� ts/null.� lg �m           