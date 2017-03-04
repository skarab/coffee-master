function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6472\" class=\"headerLeftMenuInActive\"><a id=\"aID6472\" href=\"#\" OnMouseOver=\"link('_dir','shader0',this)\" class=\"leftMenuLinkHeadInActive\">shader</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID6202\" class=\"leftMenuInActive\"><a id=\"aID6202\" href=\"#\" OnMouseOver=\"link('_class','Property0',this)\" class=\"leftMenuLinkInActive\">Property</a></div>\n");
document.write("<div id=\"divID1064\" class=\"leftMenuInActive\"><a id=\"aID1064\" href=\"#\" OnMouseOver=\"link('_class','ShaderGLSL22463',this)\" class=\"leftMenuLinkInActive\">ShaderGLSL</a></div>\n");
document.write("<div id=\"divID1065\" class=\"leftMenuInActive\"><a id=\"aID1065\" href=\"#\" OnMouseOver=\"link('_class','ShaderProperty22463',this)\" class=\"leftMenuLinkInActive\">ShaderProperty</a></div>\n");
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
