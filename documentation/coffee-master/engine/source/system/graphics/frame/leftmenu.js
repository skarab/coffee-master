function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6501\" class=\"headerLeftMenuInActive\"><a id=\"aID6501\" href=\"#\" OnMouseOver=\"link('_dir','frame0',this)\" class=\"leftMenuLinkHeadInActive\">frame</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID6357\" class=\"leftMenuInActive\"><a id=\"aID6357\" href=\"#\" OnMouseOver=\"link('_dir','buffer/buffer0',this)\" class=\"leftMenuLinkInActive\">buffer</a></div>\n");
document.write("<div id=\"divID6360\" class=\"leftMenuInActive\"><a id=\"aID6360\" href=\"#\" OnMouseOver=\"link('_dir','layer/layer0',this)\" class=\"leftMenuLinkInActive\">layer</a></div>\n");
document.write("<div id=\"divID6363\" class=\"leftMenuInActive\"><a id=\"aID6363\" href=\"#\" OnMouseOver=\"link('_dir','pass/pass0',this)\" class=\"leftMenuLinkInActive\">pass</a></div>\n");
document.write("<div id=\"divID6369\" class=\"leftMenuInActive\"><a id=\"aID6369\" href=\"#\" OnMouseOver=\"link('_dir','picker/picker0',this)\" class=\"leftMenuLinkInActive\">picker</a></div>\n");
document.write("<div id=\"divID6370\" class=\"leftMenuInActive\"><a id=\"aID6370\" href=\"#\" OnMouseOver=\"link('_dir','scissor/scissor0',this)\" class=\"leftMenuLinkInActive\">scissor</a></div>\n");
document.write("<div id=\"divID6371\" class=\"leftMenuInActive\"><a id=\"aID6371\" href=\"#\" OnMouseOver=\"link('_dir','shader/shader0',this)\" class=\"leftMenuLinkInActive\">shader</a></div>\n");
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
