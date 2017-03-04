function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6378\" class=\"headerLeftMenuInActive\"><a id=\"aID6378\" href=\"#\" OnMouseOver=\"link('_dir','renderer0',this)\" class=\"leftMenuLinkHeadInActive\">renderer</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID6379\" class=\"leftMenuInActive\"><a id=\"aID6379\" href=\"#\" OnMouseOver=\"link('_dir','state/state0',this)\" class=\"leftMenuLinkInActive\">state</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID886\" class=\"leftMenuInActive\"><a id=\"aID886\" href=\"#\" OnMouseOver=\"link('_class','Renderer54809',this)\" class=\"leftMenuLinkInActive\">Renderer</a></div>\n");
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
