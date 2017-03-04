function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6381\" class=\"headerLeftMenuInActive\"><a id=\"aID6381\" href=\"#\" OnMouseOver=\"link('_dir','source0',this)\" class=\"leftMenuLinkHeadInActive\">source</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID891\" class=\"leftMenuInActive\"><a id=\"aID891\" href=\"#\" OnMouseOver=\"link('_class','ShaderSource54809',this)\" class=\"leftMenuLinkInActive\">ShaderSource</a></div>\n");
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
