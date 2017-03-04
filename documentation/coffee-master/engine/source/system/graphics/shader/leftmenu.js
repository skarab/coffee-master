function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6380\" class=\"headerLeftMenuInActive\"><a id=\"aID6380\" href=\"#\" OnMouseOver=\"link('_dir','shader0',this)\" class=\"leftMenuLinkHeadInActive\">shader</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID6381\" class=\"leftMenuInActive\"><a id=\"aID6381\" href=\"#\" OnMouseOver=\"link('_dir','source/source0',this)\" class=\"leftMenuLinkInActive\">source</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID888\" class=\"leftMenuInActive\"><a id=\"aID888\" href=\"#\" OnMouseOver=\"link('_class','Shader54809',this)\" class=\"leftMenuLinkInActive\">Shader</a></div>\n");
document.write("<div id=\"divID889\" class=\"leftMenuInActive\"><a id=\"aID889\" href=\"#\" OnMouseOver=\"link('_class','ShaderEvaluators54809',this)\" class=\"leftMenuLinkInActive\">ShaderEvaluators</a></div>\n");
document.write("<div id=\"divID890\" class=\"leftMenuInActive\"><a id=\"aID890\" href=\"#\" OnMouseOver=\"link('_class','ShaderProperty54809',this)\" class=\"leftMenuLinkInActive\">ShaderProperty</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Functions</div>\n");
document.write("<div id=\"divID3815\" class=\"leftMenuInActive\"><a id=\"aID3815\" href=\"#\" OnMouseOver=\"link('_member','SHADER_EVALUATOR_GetType3431843765',this)\" class=\"leftMenuLinkInActive\">SHADER_EVALUATOR_GetType</a></div>\n");
document.write("<div id=\"divID3837\" class=\"leftMenuInActive\"><a id=\"aID3837\" href=\"#\" OnMouseOver=\"link('_member','SHADER_PROPERTY_TYPE_GetTypeName1571426196',this)\" class=\"leftMenuLinkInActive\" onmouseover=\"overLibLeftMenu();return overlib('SHADER_PROPERTY_TYPE_GetTypeName');\" onmouseout=\"return nd();\">SHADER_PROPERTY_TYPE_GetT.<img src=\"../../../../../../common/menunametolong.gif\"border=0></a></div>\n");
if(divID != "" && aID != "")
{
  var elemDiv = document.getElementById(divID);
  var elemA = document.getElementById(aID);
  if (elemDiv != undefined && elemA != undefined ) { // this is needed to abvoid crashing js on some memberpages 
    elemDiv.className = divClassName;
    elemA.className = aClassName;
  }
}
}
