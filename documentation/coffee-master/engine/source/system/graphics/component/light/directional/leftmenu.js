function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6347\" class=\"headerLeftMenuInActive\"><a id=\"aID6347\" href=\"#\" OnMouseOver=\"link('_dir','directional0',this)\" class=\"leftMenuLinkHeadInActive\">directional</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID849\" class=\"leftMenuInActive\"><a id=\"aID849\" href=\"#\" OnMouseOver=\"link('_class','ComponentLightDirectional54809',this)\" class=\"leftMenuLinkInActive\">ComponentLightDirectional</a></div>\n");
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
